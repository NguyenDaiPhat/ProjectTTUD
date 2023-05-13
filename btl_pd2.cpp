#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_set>
#include <algorithm>
#include <limits>

#define CAP 100
using namespace std;

struct Input {
    int numNode;
    vector<float> x;
    vector<float> y;
    vector<float> weights;  // Added: weights of the packages
    vector<int> pickupIndices;  // Added: indices of pickup points
    vector<int> deliveryIndices;  // Added: indices of delivery points
    
    Input(string data_file) {
        docFile(data_file);
        tinh_distance_matrix();
    }

    void docFile(string data_file) {
        ifstream inFile;
        inFile.open(data_file);
        if (!inFile.is_open()) {
            cout << "Unable to open file\n";
            exit(0);
        }
        numNode = 0;
        string line;
        while (getline(inFile, line)) {
            istringstream iss(line);
            string token;
            getline(iss, token, ',');
            getline(iss, token, ',');
            x.push_back(stod(token));
            getline(iss, token, ',');
            y.push_back(stod(token));
            getline(iss, token, ',');
            weights.push_back(stod(token));
            numNode++;
        }
        
        // Determine pickup and delivery indices
        for (int i = 0; i < numNode; i++) {
            if (weights[i] > 0) {  // Pickup point
                pickupIndices.push_back(i);
            } else {  // Delivery point
                deliveryIndices.push_back(i);
            }
        }
    }

    vector<vector<float>> distance;
    void tinh_distance_matrix() {
        for (int i = 0; i < numNode; i++) {
            distance.push_back(vector<float>(numNode, 0));
            for (int j = 0; j < numNode; j++) {
                distance[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
            }
        }
    }

    float getDistance(int i, int j) {
        return distance[i][j];
    }
};

struct Solution {
    Input* data;
    vector<int> tour;
    float total_distance;
    float remaining_capacity;  // Added: remaining capacity of the shipper
    
    Solution(Input* data) : data(data) {
        tour = { 0 };
        total_distance = 0;
        remaining_capacity = CAP;  // Assuming an initial maximum capacity of 100 units
    }

    void display() {
        for (int i = 0; i < data->numNode; i++) {
            cout << tour[i] << " ";
        }
        cout << total_distance << endl;
    }
};

void nearest_heuristic(Solution& s) {
    unordered_set<int> unvisited;
    for (int i = 0; i < s.data->numNode; i++) {
        unvisited.insert(i);
    }

    // Find the nearest pickup point to start
    float min_pickup_distance = numeric_limits<float>::max();
    int start_node = -1;
    for (int i : s.data->pickupIndices) {
        float distance = s.data->getDistance(0, i);
        if (distance < min_pickup_distance) {
            min_pickup_distance = distance;
            start_node = i;
        }
    }

    // Start with the nearest pickup point as the initial node
    s.tour = {0, start_node};
    s.total_distance = min_pickup_distance;

    unvisited.erase(0);                   // Remove the starting node from the unvisited set
    unvisited.erase(start_node);          // Remove the initial pickup node from the unvisited set
    s.remaining_capacity -= s.data->weights[start_node];  // Reduce the remaining capacity

    while (!unvisited.empty()) {
        int lastPoint = s.tour.back();
        float min_distance = numeric_limits<float>::max();
        int nearest_point = -1;

        // Find the nearest unvisited node
        for (auto node : unvisited) {
            float distance = s.data->getDistance(lastPoint, node);
            if (distance < min_distance) {
                min_distance = distance;
                nearest_point = node;
            }
        }

        // Check if the nearest point is a pickup or delivery point
        if (s.data->weights[nearest_point] > 0) {
            // Nearest point is a pickup point
            // Check if the remaining capacity allows picking up the package
            if (s.remaining_capacity >= s.data->weights[nearest_point]) {
                s.tour.push_back(nearest_point);
                s.total_distance += min_distance;
                s.remaining_capacity -= s.data->weights[nearest_point];
                unvisited.erase(nearest_point);
            }
        } else {
            // Nearest point is a delivery point
            // Check if the corresponding pickup point is already visited
            int pickup_index = -1;
            for (int i = 0; i < s.tour.size() - 1; i++) {
                if (s.tour[i] == nearest_point) {
                    pickup_index = i;
                    break;
                }
            }

            if (pickup_index != -1) {
                // The corresponding pickup point is visited, so it is valid to visit the delivery point
                s.tour.push_back(nearest_point);
                s.total_distance += min_distance;
                s.remaining_capacity += s.data->weights[nearest_point];
                unvisited.erase(nearest_point);
            }
        }
    }

    // Return to the starting node
    s.tour.push_back(0);
    s.total_distance += s.data->getDistance(s.tour.back(), 0);
}

void relocate(Solution& s) {
    bool improved = true;
    while (improved) {
        improved = false;
        for (int i = 1; i < s.tour.size() - 2; i++) {
            for (int j = i + 1; j < s.tour.size() - 1; j++) {
                float delta_distance = s.data->getDistance(s.tour[i - 1], s.tour[i]) +
                                       s.data->getDistance(s.tour[j], s.tour[j + 1]) -
                                       s.data->getDistance(s.tour[i - 1], s.tour[j]) -
                                       s.data->getDistance(s.tour[i], s.tour[j + 1]);

                if (delta_distance < 0) {
                    // Relocate nodes i and j
                    reverse(s.tour.begin() + i, s.tour.begin() + j + 1);
                    s.total_distance += delta_distance;
                    improved = true;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    string path = "C:/Users/Admin/Downloads/map.csv";
    Input data(path);
    Solution solution(&data);

    // Apply nearest heuristic
    nearest_heuristic(solution);

    // Apply relocation
    relocate(solution);

    // Display the final solution
    solution.display();

    return 0;
}