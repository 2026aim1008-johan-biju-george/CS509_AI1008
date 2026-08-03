#include "../headers/csr_graph_creation.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Structure to represent graph in Compressed Sparse Row (CSR) format
struct CSRGraph {
    vector<int> values; // weights of edges
    vector<int> col_idx; // column indices of edges
    vector<int> row_ptr; // row pointers for each vertex
};

// Function to read graph from file and store it in adjacency list format
bool read_graph(string& filename, vector<vector<pair<int, int>>>& adj, int& V, int& E, int& source){
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

// Function to print adjacency list
void print_adjacency_list(vector<vector<pair<int, int>>>& adj){
    for(auto neighbors : adj){
        cout << neighbors.size() << " ";
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
    vector<vector<pair<int, int>>> adj; // adjacency list

    cout << "Enter input filename: ";
    cin >> filename;

    if(!read_graph(filename, adj, V, E, source)){
        cout << "Error reading graph from file: " << filename << endl;
        return;
    }

    cout << "Adjacency list:" << endl;
    print_adjacency_list(adj);

    CSRGraph csr = convert_to_CSR(adj);
    cout << "CSR representation:" << endl;
    print_CSR(csr);
}