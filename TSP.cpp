#include "Location.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
// function to calculate the distance.
double calculateDistance(const Location &l1, const Location &l2) {
  double dx = l1.x - l2.x;
  double dy = l1.y - l2.y;
  return sqrt(dx * dx + dy * dy);
}
// Define a function to use a nearest neighbor heuristic to find a route(Greedy)
vector<Location> nearestNeighbor(const vector<Location> &locations) {
  // Create a vector to hold the locations
  vector<Location> orderedLocations;
  
  // Add the first location to the vector.
  orderedLocations.push_back(locations[0]);
  
  // vector to hold the remaining locations
  vector<Location> remainingLocations;
  remainingLocations.resize(locations.size() - 1);
  // Copy the remaining locations from the input vector to the new vector.
  copy(locations.begin() + 1, locations.end(), remainingLocations.begin());
  
  // Run through the remaining locations by picking the closest first
  while (!remainingLocations.empty()) {
    Location nearestLocation = remainingLocations[0];
    double nearestDistance = 1e9;
    
    // Find the location in the remaining locations that is nearest to the last
    // location in the vector.
    for (int i = 0; i < remainingLocations.size(); i++) {
      double distance = calculateDistance(orderedLocations[orderedLocations.size()-1], remainingLocations[i]);
      if (distance < nearestDistance) {
        nearestLocation = remainingLocations[i];
        nearestDistance = distance;
      }
    }
    
    // Remove it after adding it to the orderdLocations
    orderedLocations.push_back(nearestLocation);
    remainingLocations.erase(remove(remainingLocations.begin(), remainingLocations.end(), nearestLocation), remainingLocations.end());
  }
  
  return orderedLocations;
}


void twoOpt(vector<Location> &route) {
    
    bool improved = true;

    // Repeat until no further improvements can be made.
    while (improved) {
        // Set the improved flag to false.
        improved = false;

        // Consider each locations in the route.
        for (int i = 0; i < route.size(); i++) {
            for (int j = i + 2; j < route.size(); j++) {
                // Calculate the distances between the locations in the current route.
                double d1 = calculateDistance(route[i], route[i + 1]);
                double d2 = calculateDistance(route[j], route[(j + 1) % route.size()]);
                double d3 = calculateDistance(route[i], route[j]);
                double d4 = calculateDistance(route[i + 1], route[(j + 1) % route.size()]);

                // If swapping the order of the locations would result in a shorter
                // route, reverse the locations
                if (d1 + d2 > d3 + d4) {
                    reverse(route.begin() + i + 1, route.begin() + j + 1);
                    improved = true;
                }
            }
        }
    }

    // Return the improved route.
    return;
}

double calculateLength(const vector<Location> &locations) {
  double length = 0;
  for (int i = 0; i < locations.size() - 1; i++) {
    length += calculateDistance(locations[i], locations[i + 1]);
  }
  // add the cost of going from the last city back to the start
  length += calculateDistance(locations[locations.size()-1], locations[0]);
  return length;
}

int main() { 
  string filename;
    ifstream InputFile;
    ofstream OutputFile;
    cout << "File name: ";
    cin >> filename;
    InputFile.open(filename.data());

    while (!InputFile.is_open()) {
      cout << "Wrong filename! Please try again: ";
      InputFile.clear();
      cout << "File name: ";
      cin >> filename;
      InputFile.open(filename.data());
    }
  // Read the number of locations from the input file.
    double temp;
    InputFile >> temp;
    double N= temp;
  // Read the locations from the input file.
    vector<Location> locations;
    locations.resize(N);
    for (int i = 0; i < N; i++){
      double X, Y;
      InputFile>> temp;
      X = temp;
      InputFile >> temp;
      Y = temp;
      locations[i].x = X ;
      locations[i].y = Y;
      locations[i].rank = i;
    }
  // Find a starting point using the nearestNeighbor heuristic
  vector<Location> route = nearestNeighbor(locations);
  // Use the two-opt algorithm to improve the route.
    twoOpt(route);
   
  OutputFile.open("output-" + filename);
    OutputFile << calculateLength(route) << endl;
    for (int i = 0; i < route.size(); i++) {
      OutputFile << route[i].rank  << " ";
    }

  
  }