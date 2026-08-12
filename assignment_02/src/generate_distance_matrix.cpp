#include "../headers/distance_matrix_generator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a dense adjacency matrix
void generate_distance_matrix(int V, double edge_probability=0.3, bool allow_negative=false){
    string filename = "tests/fw_" + to_string(V) + ".txt";
    ofstream fout(filename);

    if(!fout){
        cout << "Cannot create file: " << filename << endl;
        return;
    }
    
    // initialize (V x V) matrix with all infinity values
    vector<vector<int>> matrix(V, vector<int>(V, INT_MAX));

    // Generate direct edges
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            // Distance from a vertex to itself is always zero
            if(i==j){
                matrix[i][j] = 0;
                continue;
            }
            
            // Decide whether a direct edge exists
            double probability = (double)rand()/RAND_MAX;
            if(probability <= edge_probability){
                // Generate edge
                int weight;
                if(allow_negative){
                    weight = (rand() % 21) - 10; // weights are from -10 to 10
                }
                else{
                    weight = (rand() % 10) + 1; // weights are from 1 to 10
                }
                matrix[i][j] = weight;
            }
        }
    }
    

    fout << V << endl; // Write no. of vertices to file

    // Write matrix to file
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(matrix[i][j]==INT_MAX)
                fout << "INF ";
            else
                fout << matrix[i][j] << " ";
        }
        fout << endl;
    }
    fout.close();
}

void generate_distance_matrix_tests(){
    generate_distance_matrix(500);
    generate_distance_matrix(1000);
    generate_distance_matrix(2000);
}