// to run:
//  ./a inputfile outputfile

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <cmath>

using namespace std;

// I'm a bad person
vector<vector<double> > Distances;
  vector<vector<double> > Vertices;

double distance(double x1, double y1, double x2, double y2){
  return sqrt(pow (x1-x2,2.0) + pow (y1-y2,2.0));
}

double Compute_Distance(int v1, int v2){
  if(v1 <= v2)
    return Distances[v1][v2-v1];
  else
    return Compute_Distance(v2,v1);
}


double tour_dist(const vector<int>& tour){
 double tour_length = 0;
  int prev = tour[tour.size()-1];
  for(int i = 0; i < tour.size(); i++){
    tour_length += Compute_Distance(prev, tour[i]);
    prev = tour[i];
  }
  return tour_length;
}


int main(int argc, char* argv[]){
  // cout << "Enter the input file name: ";
  string input_filename = argv[1];
  cout << "Input is: " << input_filename << endl;
  // cin >> input_filename;
  ifstream input;
  input.open(input_filename.data());
  assert(input.is_open());
  // cout << "Enter the output file name: ";
  string output_filename = argv[2];
  cout << "Output is: " << output_filename << endl;
  //  cin >> output_filename;
  ifstream output;
  output.open(output_filename.data());
  assert(output.is_open());
  int num_vertices;
  input >> num_vertices;


  Vertices.resize(num_vertices);
  for(int i = 0; i < num_vertices; i++){
    Vertices[i].resize(2);
    input >> Vertices[i][0];
    input >> Vertices[i][1];
  }
  cerr << "vertices read" << endl;

  

  Distances.resize(num_vertices);
  for(int i = 0; i < num_vertices; i++){
    Distances[i].resize(num_vertices-i);
    
    for(int j = 0; j < Distances[i].size(); j++){
      //    cout << "Computing distance from vertex " << i << " to " << i+j << endl;
      Distances[i][j] = distance(Vertices[i][0],Vertices[i][1], Vertices[i+j][0], Vertices[i+j][1]);
     
    }
  }
  double claimed_length;
  output >> claimed_length;
  vector<int> tour(num_vertices);
  vector<bool> taken(num_vertices, false);
  for(int i = 0; i < num_vertices; i++){
    output >> tour[i];
    if(taken[tour[i]])
      cout << "Error: Vertex " << tour[i] << " used twice!" << endl;
    else
      taken[tour[i]] = true;
   
  }
  for(int i = 0; i < taken.size(); i++){
    if(!taken[i])
      cout << "Error: Vertex " << i << " not used!" << endl;
  }
  
  double tour_length = tour_dist(tour);
  // check by hand whether any differences are from roundoff
  cout << "Claimed length : " << claimed_length;
  cout << "Actual length: " << tour_length;
  return 0;
}