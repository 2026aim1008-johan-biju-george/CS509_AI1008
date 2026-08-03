#include "../headers/matrix_generator.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate random matrices and write them to file
void generate_matrices(int id, int M, int K, int N){
    string filename = "tests/gemm_test_0" + to_string(id) + ".txt"; // input filename
    ofstream fout(filename); // output file pointer
    if(!fout){
        cout << "Cannot create file: "<< filename << endl;
        return;
    }

    fout << M << " " << K << " " << N << endl; // write matrix dimensions to file
    
    // generate random values for matrix A, and write them to the file
    for(int i=0;i<M;i++){
        for(int j=0;j<K;j++){
            fout << rand() % 10 << " ";
        }
        fout << endl;
    }
    
    // generate random values for matrix B, and write them to the file
    for(int i=0;i<K;i++){
        for(int j=0;j<N;j++){
            fout << rand() % 10 << " ";
        }
        fout << endl;
    }

    fout.close();
    cout << "Test case generated" << endl;
}

void generate_matrix_tests(){
    generate_matrices(1, 4, 4, 4);
    generate_matrices(2, 16, 16, 16);
    generate_matrices(3, 32, 32, 32);
    generate_matrices(4, 64, 64, 64);
    generate_matrices(5, 128, 128, 128);
    generate_matrices(6, 256, 256, 256);
    generate_matrices(7, 512, 512, 512);
}