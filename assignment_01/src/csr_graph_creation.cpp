#include "../headers/csr_graph_creation.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

// function to read unweighted graph from file into adjacency list
bool read_unweighted_graph(string& filename, vector<vector<int>>& adj, int& V, int& E, int& source){
    ifstream fin(filename); // input file pointer
    if(!fin){
        cout << "Cannot open file: " << filename << endl;
        return false;
    }
    
    fin >> V >> E; // read input of number of vertices and edges
    adj.assign(V, vector<int>()); // initialize adjacency list
    // read the adjacency list from file, and populate the adjacency list vector
    for(int i=0;i<V;i++){
        int node, degree;
        fin >> node >> degree;
        for(int j=0;j<degree;j++){
            int neighbor;
            fin >> neighbor;
            adj[node].push_back(neighbor);
        }
    }
    // read the source vertex from file
    string source_label;
    fin >> source_label >> source;

    fin.close();
    return true;
}

// function to read unweighted graph from file into adjacency list
bool read_weighted_graph(string& filename, vector<vector<pair<int, int>>>& adj, int& V, int& E, int& source){
    ifstream fin(filename); // input file pointer
    if(!fin){
        cout << "Cannot open file: " << filename << endl;
        return false;
    }
    
    fin >> V >> E; // read input of number of vertices and edges
    adj.assign(V, vector<pair<int, int>>()); // initialize adjacency list
    // read the adjacency list from file, and populate the adjacency list vector
    for(int i=0;i<V;i++){
        int node, degree;
        fin >> node >> degree;
        for(int j=0;j<degree;j++){
            int neighbor, weight;
            fin >> neighbor >> weight;
            adj[node].push_back({neighbor, weight});
        }
    }
    // read the source vertex from file
    string source_label;
    fin >> source_label >> source;

    fin.close();
    return true;
}

// function to convert adjacency list to CSR format
CSRGraph convert_unweighted_graph_to_CSR(vector<vector<int>>& adj){
    CSRGraph csr;
    int V = adj.size(); // number of vertices
    csr.row_ptr.push_back(0); // first row pointer is always zero

    for(int nodes=0;nodes<V;nodes++){
        for(auto neighbor : adj[nodes]){
            csr.values.push_back(1); // assuming unweighted graph, all edges have weight 1
            csr.col_idx.push_back(neighbor); // populate column indices by adding neighbors to col_idx vector
        }
        // cumulative edge count so far -> end offset for this vertex's edges
        csr.row_ptr.push_back(csr.col_idx.size());
    }

    return csr;
}

CSRGraph convert_weighted_graph_to_CSR(vector<vector<pair<int, int>>>& adj){
    CSRGraph csr;
    int V = adj.size(); // number of vertices
    csr.row_ptr.push_back(0); // first row pointer is always zero

    for(int nodes=0;nodes<V;nodes++){
        for(auto neighbor : adj[nodes]){
            csr.values.push_back(neighbor.second); // edge weights
            csr.col_idx.push_back(neighbor.first); // populate column indices by adding neighbors to col_idx vector
        }
        // cumulative edge count so far -> end offset for this vertex's edges
        csr.row_ptr.push_back(csr.col_idx.size());
    }

    return csr;
}

// Function to print adjacency list
void print_adjacency_list(vector<vector<pair<int, int>>>& adj){
    for(auto neighbors : adj){
        cout << neighbors.size() << " "; // degree
        for(auto neighbor : neighbors){
            cout << neighbor.first << "(" << neighbor.second << ") ";
        }
        cout << endl;
    }
}

// Function to convert adjacency list to CSR format
CSRGraph convert_to_CSR(vector<vector<pair<int, int>>>& adj){
    CSRGraph csr;
    int V = adj.size(); // number of vertices
    csr.row_ptr.push_back(0); // first row pointer is always zero

    for(int nodes=0;nodes<V;nodes++){
        for(auto neighbor : adj[nodes]){
            csr.values.push_back(neighbor.second); // populate values with edge weights
            csr.col_idx.push_back(neighbor.first); // populate column indices by adding neighbors to col_idx vector
        }
        // populate row pointers by keeping track of number of edges for each vertex
        csr.row_ptr.push_back(csr.col_idx.size());
    }

    return csr;
}

// Function to print CSR format of graph
void print_CSR(CSRGraph& csr){
    cout << "Values: ";
    for(auto val : csr.values){
        cout << val << " ";
    }
    cout << endl;

    cout << "Column Indices: ";
    for(auto col : csr.col_idx){
        cout << col << " ";
    }
    cout << endl;

    cout << "Row Pointers: ";
    for(auto row : csr.row_ptr){
        cout << row << " ";
    }
    cout << endl;
}

// Main function to run CSR graph generation
void run_csr_graph(){
    int V, E, source;
    string filename; // input filename
    vector<vector<pair<int, int>>> adj; // adjacency list (weighted)

    cout << "Enter input filename: ";
    cin >> filename;

    if(!read_weighted_graph(filename, adj, V, E, source)){
        cout << "Error reading graph from file: " << filename << endl;
        return;
    }

    cout << "Adjacency list:" << endl;
    print_adjacency_list(adj);

    CSRGraph csr = convert_to_CSR(adj);
    cout << "CSR representation:" << endl;
    print_CSR(csr);
}