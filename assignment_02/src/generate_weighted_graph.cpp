#include "../headers/graph_generator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void write_distance_matrix(vector<vector<pair<int,int>>>& adj, int V){
    string filename = "tests/fw_" + to_string(V) + ".txt";
    ofstream fout(filename);

    if(!fout){
        cout << "Cannot create file: " << filename << endl;
        return;
    }

    fout << V << endl;

    vector<vector<int>> matrix(V, vector<int>(V, INT_MAX));

    // Use the same adjacency list
    for(int u = 0; u < V; u++){
        matrix[u][u] = 0;
        for(auto edge : adj[u]){
            int v = edge.first;
            int weight = edge.second;
            matrix[u][v] = weight;
        }
    }

    // Write matrix
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(matrix[i][j] == INT_MAX)
                fout << "INF";
            else
                fout << matrix[i][j];

            if(j != V-1)
                fout << " ";
        }
        fout << endl;
    }

    fout.close();
}

// function to generate weighted graph and write it to file
void generate_weighted_graph(string algorithm, int V, int E, int source, double negative_edge_percentage, bool directed=true){
    string filename = "tests/" + algorithm + "_" + to_string(V) + ".txt"; // input filename
    ofstream fout(filename); // output file pointer
    if(!fout){
        cout << "Cannot create file: "<< filename << endl;
        return;
    }
    
    // calculate number of maximum edges and check if the number of edges exceeds the maximum possible number of edges without self-loops
    long long max_edges;
    if(directed)
        max_edges = 1LL * V * (V-1);
    else
        max_edges = 1LL * V * (V-1) / 2;

    if(E > max_edges){
        cout << "Not possible to create the graph as the number of edges exceeds the maximum possible number of edges.\n";
        return;
    }

    vector<vector<pair<int, int>>> adj(V); // adjacency list (weighted graph)

    int negative_edges = (int)(E * negative_edge_percentage);
    
    int edges = 0;
    while(edges < E){
        int u = rand() % V; // random vertex u
        int v = rand() % V; // random vertex v
        
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
            int weight;
            if(negative_edges > 0){
                weight = -((rand() % 10) + 1); // weights -> [-10...-1]
                negative_edges--;
            }
            else{
                weight = (rand() % 10) + 1; // weights -> [1...10]
            }
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
    
    // to cross check with Floyd-Warshall graph
    if(V == 10 || V == 100){
        write_distance_matrix(adj, V);
    }
}

// main function to generate weighted graph test cases
void generate_weighted_tests(){
    generate_weighted_graph("bf", 10, 20, 0, 0.0);
    generate_weighted_graph("bf", 100, 200, 0, 0.0);
    generate_weighted_graph("bf", 10000, 20000, 0, 0.3);
    generate_weighted_graph("bf", 50000, 100000, 0, 0.35);
    generate_weighted_graph("bf", 100000, 200000, 0, 0.4);
}