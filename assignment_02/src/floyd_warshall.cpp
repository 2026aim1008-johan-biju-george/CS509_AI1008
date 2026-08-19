#include "../headers/floyd_warshall.h"
#include "../headers/bellman_ford.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <chrono>

using namespace std;

bool read_distance_matrix(string& filename, vector<vector<int>>& distance, int& V){
    ifstream fin(filename);

    if(!fin) {
        cout << "Cannot open file: " << filename << endl;
        return false;
    }

    fin >> V; // read no. of vertices from file

    distance.assign(V, vector<int>(V, INT_MAX)); // (N x N) matrix

    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            string value;
            fin >> value;

            if(value == "INF"){
                distance[i][j] = INT_MAX;
            }
            else{
                distance[i][j] = stoi(value);
            }
        }
    }

    fin.close();
    return true;
}

void floyd_warshall(int V, vector<vector<int>>& distance){
    // go through all k intermediate nodes
    for(int k=0;k<V;k++){
        // go through all i source nodes
        for(int i=0;i<V;i++){
            if(distance[i][k] == INT_MAX) continue;
            // go through all j destination nodes
            for(int j=0;j<V;j++){
                if(distance[k][j] == INT_MAX) continue;
                if(distance[i][k] + distance[k][j] < distance[i][j]){
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
}

bool has_negative_cycle(int V, vector<vector<int>>& distance){
    for(int i=0;i<V;i++) {
        if(distance[i][i] < 0) return true;
    }
    return false;
}

void run_floyd_warshall(int V, vector<vector<int>>& distance){
    auto start_time = chrono::high_resolution_clock::now(); // Start timer for Floyd Warshall
    floyd_warshall(V, distance);
    auto end_time = chrono::high_resolution_clock::now(); // End timer for Floyd Warshall
    
    auto duration = chrono::duration<double, milli>(end_time - start_time).count();
    bool negative_cycle = has_negative_cycle(V, distance);

    cout << "Algorithm: Floyd-Warshall\n";
    if(negative_cycle){
        cout << "Negative cycle: true\n";
    }
    else{
        cout << "Distance matrix:\n";
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++){
                if(distance[i][j] == INT_MAX){
                    cout << "INF ";
                }
                else{ 
                    cout << distance[i][j] << " ";
                }
            }
            cout << endl;
        }
        cout << "Negative cycle: none\n";
    }
    cout << "Execution time: " << duration << " ms\n\n";
}

void cross_check(int V){
    string bf_filename = "tests/bf_" + to_string(V) + ".txt";
    string fw_filename = "tests/fw_" + to_string(V) + ".txt";

    // Read Floyd-Warshall input
    vector<vector<int>> fw_distance;
    int fw_V;

    if(!read_distance_matrix(fw_filename, fw_distance, fw_V)){
        cout << "Cannot read " << fw_filename << endl;
        return;
    }

    // Read Bellman-Ford input
    vector<vector<pair<int,int>>> adj;
    int bf_V, E, source;

    if(!read_weighted_graph(bf_filename, adj, bf_V, E, source)){
        cout << "Cannot read " << bf_filename << endl;
        return;
    }

    // Convert Bellman-Ford graph to CSR using Assignment 1 function
    CSRGraph csr = convert_weighted_graph_to_CSR(adj);

    // Run Floyd-Warshall
    floyd_warshall(V, fw_distance);

    bool passed = true; // flag to check whether cross-check passed or not

    // Run Bellman-Ford from every vertex
    for(int source = 0; source < V; source++){
        vector<int> bf_distance(V, INT_MAX);
        if(!bellman_ford(source, csr, V, bf_distance)){
            cout << "Negative cycle detected for V = "<< V << ", source = " << source << endl;
            return;
        }

        // Compare Bellman-Ford result with Floyd-Warshall row
        for(int v=0;v<V;v++){
            if(bf_distance[v] != fw_distance[source][v]){
                passed = false;
                cout << "Mismatch: " << "Source = " << source << ", Vertex = " << v << endl;
                cout << "Bellman-Ford = " << bf_distance[v] << endl;
                cout << "Floyd-Warshall = " << fw_distance[source][v] << endl;
                break;
            }
        }
        if(!passed) break;
    }

    if(passed){
        cout << "Cross-check passed for V = " << V << endl;
    }
    else{
        cout << "Cross-check failed for V = " << V << endl;
    }
}

void run_cross_checks(){
    cout << "Cross-checking graph of 10 vertices\n";
    cross_check(10);

    cout << "Cross-checking graph of 100 vertices\n";
    cross_check(100);
}

void run_floyd_warshall_test() {
    int V;
    string filename;

    vector<vector<int>> distance;

    cout << "Enter input filename: ";
    cin >> filename;

    if(!read_distance_matrix(filename, distance, V)){
        cout << "Error reading distance matrix from file: " << filename << endl;
        return;
    }

    run_floyd_warshall(V, distance);
}

