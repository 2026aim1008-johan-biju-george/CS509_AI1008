#include "../headers/graph_generator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate weighted undirected graph and write it to file
void generate_weighted_graph(int V, int E){
    string filename = "tests/mst_" + to_string(V) + ".txt";
    ofstream fout(filename);

    if(!fout){
        cout << "Cannot create file: " << filename << endl;
        return;
    }

    long long max_edges = 1LL * V * (V-1) / 2;
    if(V-1 > E || E > max_edges){
        cout << "Invalid number of edges for V = " << V << endl;
        return;
    }

    vector<vector<pair<int, int>>> adj(V);

    // Create connected graph
    int edges = 0;
    for(int v = 1; v < V; v++){
        int u = rand() % v;
        int weight = rand() % 10 + 1;

        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
        edges++;
    }

    // Add remaining random edges
    while(edges < E){
        int u = rand() % V; // random vertex u
        int v = rand() % V; // random vertex v

        if(u == v){
            continue;
        }
        
        // Check for duplicate edges
        bool exists = false;
        for(auto edge : adj[u]){
            if(edge.first == v){
                exists = true;
                break;
            }
        }

        if(exists){
            continue;
        }

        int weight = rand() % 10 + 1;
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
        edges++;
    }

    // Write graph to file
    fout << V << " " << E << endl;
    for(int u=0;u<V;u++){
        fout << u << " " << adj[u].size();
        for(auto edge : adj[u]){
            fout << " " << edge.first << " " << edge.second;
        }
        fout << endl;
    }
    fout.close();
}

// Main function to generate weighted graph test cases
void generate_weighted_tests(){
    generate_weighted_graph(10, 20);
    generate_weighted_graph(100, 200);
    generate_weighted_graph(10000, 20000);
    generate_weighted_graph(50000, 100000);
    generate_weighted_graph(100000, 200000);
}