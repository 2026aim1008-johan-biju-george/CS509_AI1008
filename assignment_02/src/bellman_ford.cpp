#include "../headers/bellman_ford.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <climits>

using namespace std;

// Bellman Ford algorithm
bool bellman_ford(int source, CSRGraph& graph, int V, vector<int>& distance){
    distance[source] = 0;

    // relaxing edges 'V-1' times
    for(int i=0;i<V-1;i++){
        for(int node=0;node<V;node++){
            if(distance[node] == INT_MAX) continue;
            int start_edge = graph.row_ptr[node];
            int end_edge = graph.row_ptr[node+1];

            for(int j=start_edge;j<end_edge;j++){
                int neighbor = graph.col_idx[j];
                int weight = graph.values[j];

                if(distance[node] + weight < distance[neighbor]){
                    distance[neighbor] = distance[node] + weight;
                }
            }
        }
    }

    // negative cycle detection
    for(int node=0;node<V;node++){
        if(distance[node] == INT_MAX) continue;
        int start_edge = graph.row_ptr[node];
        int end_edge = graph.row_ptr[node+1];

        for(int j=start_edge;j<end_edge;j++){
            int neighbor = graph.col_idx[j];
            int weight = graph.values[j];
            // negative cycle detected
            if(distance[node] + weight < distance[neighbor]){
                return false;
            }
        }
    }

    return true;
}

// function to run Bellman Ford on CSR graph
void run_bellman_ford(CSRGraph& graph, int V, int source){
    vector<int> distance(V, INT_MAX); // initialize distances to infinity
    
    auto start_time = chrono::high_resolution_clock::now(); // Start timer for bellman_ford
    bool no_negative_cycle = bellman_ford(source, graph, V, distance);
    auto end_time = chrono::high_resolution_clock::now(); // End timer for bellman_ford
    
    auto duration = chrono::duration<double, milli>(end_time - start_time).count();
    cout << "Algorithm: Bellman-Ford\nSource: " << source << "\n";
    if(!no_negative_cycle){
        cout << "Negative cycle: true\n";
    }
    else{
        cout << "Vertex Distance\n";
        for(int i=0;i<V;i++){
            if(distance[i]==INT_MAX){ 
                cout << i << "      " << "INF\n";
            }
            else{
                cout << i << "      " << distance[i] << "\n";
            }
        }
        cout << "Negative cycle: none\n";
    }
    cout << "Execution time: " << duration << " ms\n\n";
}

// function to run Bellman Ford test
void run_bellman_ford_test(){
    int V, E, source; // number of vertices and edges, and source node
    string filename; // input filename
    vector<vector<pair<int, int>>> adj; // adjacency list (weighted graph)

    cout << "Enter input filename: ";
    cin >> filename;
    
    // read graph from file and populate adjacency list
    if(!read_weighted_graph(filename, adj, V, E, source)){
        cout << "Error reading graph from file: " << filename << endl;
        return;
    }

    CSRGraph csr = convert_weighted_graph_to_CSR(adj); // convert adjacency list to CSR format
    run_bellman_ford(csr, V, source);
}