#include "../headers/prim.h"
#include "../headers/csr_graph_creation.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <queue>

using namespace std;

int prim_MST(int V, CSRGraph& csr, vector<vector<int>>& mst_edges){
    vector<int> visited(V, 0);

    // Store edges in the form {weight, u, v} into min-priority queue
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    
    int source = 0;
    int total_weight = 0;
    visited[source] = 1;

    // Add all edges of source node into priority queue
    int start = csr.row_ptr[source];
    int end = csr.row_ptr[source + 1];
    for(int i=start;i<end;i++){
        int v = csr.col_idx[i];
        int weight = csr.values[i];
        pq.push({weight, source, v});
    }

    while(!pq.empty() && mst_edges.size() < V-1){
        vector<int> edge = pq.top();
        pq.pop();

        int weight = edge[0];
        int u = edge[1];
        int v = edge[2];

        // Skip if node v is already part of MST
        if(visited[v]){
            continue;
        }

        visited[v] = 1;
        mst_edges.push_back({u, v, weight}); // Add edge to MST
        total_weight += weight;

        // Add edges from new node into priority queue
        start = csr.row_ptr[v];
        end = csr.row_ptr[v + 1];
        for(int i=start;i<end;i++){
            int next = csr.col_idx[i];
            int weight = csr.values[i];
            if(!visited[next]){
                pq.push({weight, v, next});
            }
        }
    }

    return total_weight;
}

double run_prim(int V, CSRGraph& csr, vector<vector<int>>& mst_edges){
    auto start = chrono::high_resolution_clock::now(); // Start time
    int total_weight = prim_MST(V, csr, mst_edges);
    auto end = chrono::high_resolution_clock::now(); // End time
    double execution_time = chrono::duration<double, milli>(end - start).count();

    cout << "Algorithm: Prim's MST" << endl;
    if(V < 10000){
        cout << "MST edges:\n";
        for(int i=0;i<mst_edges.size();i++){
            int u = mst_edges[i][0];
            int v = mst_edges[i][1];
            int weight = mst_edges[i][2];
            cout << u << " " << v << " " << weight << endl;
        }
    }
    cout << "Total MST weight: " << total_weight << endl;
    cout << "Execution time: " << execution_time << " ms" << endl;
    return total_weight;
}

void run_prim_test(){
    int V, E;
    string filename; // input filename
    vector<vector<pair<int, int>>> adj; // adjacency list (weighted)
    vector<vector<int>> mst_edges; // MST edge list (stored in the form {u, v, weight})

    cout << "Enter input filename: ";
    cin >> filename;
    
    // read graph from file and populate adjacency list
    if(!read_weighted_graph(filename, adj, V, E)){
        cout << "Error reading graph from file: " << filename << endl;
        return;
    }

    CSRGraph csr = convert_weighted_graph_to_CSR(adj); // convert adjacency list to CSR format
    run_prim(V, csr, mst_edges);
}