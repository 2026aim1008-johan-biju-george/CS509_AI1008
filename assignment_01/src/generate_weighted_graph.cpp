#include "../headers/graph_generator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate weighted graph and write it to file
void generate_weighted_graph(int V, int E, int source, bool directed=false){
    string filename = "tests/graph_" + to_string(V) + ".txt";
    ofstream fout(filename);
    if(!fout){
        cout << "Cannot create file: "<< filename << endl;
        return;
    }
    
    // check if the number of edges exceeds the maximum possible number of edges without self-loops
    long long max_edges;

    if(directed)
        max_edges = 1LL * V * (V - 1);
    else
        max_edges = 1LL * V * (V - 1) / 2;

    if(E > max_edges){
        cout << "Not possible to create the graph as the number of edges exceeds the maximum possible number of edges.\n";
        return;
    }

    vector<vector<pair<int, int>>> adj(V); // adjacency list (weighted graph)

    // First pass: add one outgoing edge for as many vertices as possible
    int edges = 0;
    for(int u=0;u<V && edges<E;u++){
        int v;
        do {
            v = rand() % V;
        } while (v == u);

        int weight = rand() % 10 + 1;
        adj[u].push_back({v, weight});
        edges++;

        // for undirected graph, store both directions.
        if(!directed && edges <= E){
            adj[v].push_back({u, weight});
        }
    }

    // Second pass: add remaining random edges
    while(edges < E){
        int u = rand() % V; // random vertex u
        int v = rand() % V; // random vertex v
        int weight = rand() % 10 + 1; // positive random weight for edge
        
        // check for duplicate edges
        bool exists = false;
        for(auto edge : adj[u]){
            if(edge.first == v){
                exists = true;
                break;
            }
        }
        if(!directed){
            for(auto edge : adj[v]){
                if(edge.first == u){
                    exists = true;
                    break;
                }
            }
        }

        // push the edge to adjacency list if it's not a duplicate and not the same as the node itself (to avoid self-loops)
        if(!exists && u != v){
            adj[u].push_back({v, weight});
            if(!directed){
                adj[v].push_back({u, weight});
            }
            edges++;
        }
    }
    
    fout << V << " " << E << endl; // write number of vertices and edges to file

    // write adjacency list to file
    for (int node=0;node<V;node++){
        fout << node << " " << adj[node].size() << " "; // write node and its degree
        for(auto neighbor : adj[node]){
            fout << neighbor.first << " " << neighbor.second << " "; // write neighbors and their weights
        }
        fout << endl;
    }

    // write source vertex to file
    fout << "SOURCE " << source << endl;
    fout.close();
}

// Main function to generate weighted graph test cases
void generate_weighted_tests(){
    generate_weighted_graph(10, 20, 0);
    generate_weighted_graph(100, 200, 0);
    generate_weighted_graph(10000, 20000, 0);
    generate_weighted_graph(50000, 100000, 0);
    generate_weighted_graph(100000, 200000, 0);
}