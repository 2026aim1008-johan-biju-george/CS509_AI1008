#include "../headers/kruskal.h"
#include "../headers/csr_graph_creation.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

class Disjoint_Set{
private:
    vector<int> parent;
    vector<int> size;

public:
    Disjoint_Set(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for(int i=0;i<n;i++){
            parent[i] = i;
        }
    }

    int find_ultimate_parent(int node) {
        if(parent[node] != node){
            parent[node] = find_ultimate_parent(parent[node]);
        }
        return parent[node];
    }

    void union_by_size(int u, int v) {
        int root_u = find_ultimate_parent(u);
        int root_v = find_ultimate_parent(v);

        if(root_u == root_v){
            return;
        }
        else if(size[root_u] > size[root_v]){
            parent[root_v] = root_u;
            size[root_u] += size[root_v];
        }
        else{
            parent[root_u] = root_v;
            size[root_v] += size[root_u];
        }
    }
};


int kruskal_MST(int V, CSRGraph& csr, vector<vector<int>>& mst_edges){
    vector<vector<int>> edges; // store each edge in the form {weight, u, v}

    // Extract edges from CSR
    for(int u=0;u<V;u++){
        int start = csr.row_ptr[u];
        int end = csr.row_ptr[u + 1];

        for(int i=start;i<end;i++){
            int v = csr.col_idx[i];
            int weight = csr.values[i];

            // Avoid duplicate copy of undirected edge
            if(u < v){
                edges.push_back({weight, u, v});
            }
        }
    }

    // Sort edges by increasing weight
    sort(edges.begin(), edges.end());

    Disjoint_Set ds(V);
    
    // visit each edge and add it to MST if the connected nodes of that edge aren't in same Disjoint Set
    int total_weight = 0;
    for(auto edge:edges){
        int weight = edge[0];
        int u = edge[1];
        int v = edge[2];
        if(ds.find_ultimate_parent(u) != ds.find_ultimate_parent(v)){
            total_weight += weight;
            mst_edges.push_back(edge);
            ds.union_by_size(u, v);
            if(mst_edges.size() == V-1){
                break;
            }
        }
    }

    return total_weight;
}

double run_kruskal(int V, CSRGraph& csr, vector<vector<int>>& mst_edges){
    auto start = chrono::high_resolution_clock::now(); // Start time
    int total_weight = kruskal_MST(V, csr, mst_edges);
    auto end = chrono::high_resolution_clock::now(); // End time
    double execution_time = chrono::duration<double, milli>(end - start).count();
    
    cout << "Algorithm: Kruskal's MST" << endl;
    if(V < 10000){
        cout << "MST edges:\n";
        for(int i=0;i<mst_edges.size();i++){
            int u = mst_edges[i][1];
            int v = mst_edges[i][2];
            int weight = mst_edges[i][0];
            cout << u << " " << v << " " << weight << endl;
        }
    }
    cout << "Total MST weight: " << total_weight << endl;
    cout << "Execution time: " << execution_time << " ms" << endl;
    return total_weight;
}

void run_kruskal_test(){
    int V, E;
    string filename; // input filename
    vector<vector<pair<int, int>>> adj; // adjacency list (weighted)
    vector<vector<int>> mst_edges; // MST edge list

    cout << "Enter input filename: ";
    cin >> filename;
    
    // read graph from file and populate adjacency list
    if(!read_weighted_graph(filename, adj, V, E)){
        cout << "Error reading graph from file: " << filename << endl;
        return;
    }

    CSRGraph csr = convert_weighted_graph_to_CSR(adj); // convert adjacency list to CSR format
    run_kruskal(V, csr, mst_edges);
}