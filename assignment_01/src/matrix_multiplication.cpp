#define BLOCK_SIZE 32

#include "../headers/matrix_multiplication.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

// Helper function for simple matrix multiplication
void simple_GEMM(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int M, int K, int N){
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            for(int k=0;k<K;k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Helper function for blocking matrix multiplication
void blocking_GEMM(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int M, int K, int N, int block_size){
    for(int ii=0;ii<M;ii+=block_size){
        for(int jj=0;jj<N;jj+=block_size){
            for(int kk=0;kk<K;kk+=block_size){
                for(int i=ii;i<min(ii+block_size, M);i++){
                    for(int j=jj;j<min(jj+block_size, N);j++){
                        for(int k=kk;k<min(kk+block_size, K);k++){
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

// Function to read matrices from file and store them in 2D vectors
bool read_matrices(string& filename, vector<vector<int>>& A, vector<vector<int>>& B, int& M, int& K, int& N){
    ifstream fin(filename); // input file pointer
    if(!fin){
        cout << "Error opening file: "<< filename << endl;
        return false;
    }

    fin >> M >> K >> N; // read matrix dimensions from file

    A.assign(M, vector<int> (K)); // assign matrix A to dimension (M x K)
    B.assign(K, vector<int> (N)); // assign matrix B to dimension (K x N)
    
    // read matrix A from file
    for(int i=0;i<M;i++){
        for(int j=0;j<K;j++){
            fin >> A[i][j];
        }
    }
    
    // read matrix B from file
    for(int i=0;i<K;i++){
        for(int j=0;j<N;j++){
            fin >> B[i][j];
        }
    }

    fin.close();
    return true;
}

// Function to print matrix
void print_matrix(vector<vector<int>>& matrix, int rows, int cols){
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to run simple matrix multiplication
void run_simple_GEMM(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int M, int K, int N){
    auto start = chrono::high_resolution_clock::now(); // start timer for simple GEMM
    simple_GEMM(A, B, C, M, K, N);
    auto stop = chrono::high_resolution_clock::now(); // end timer for simple GEMM

    auto duration = chrono::duration<double, milli>(stop-start).count();

    cout << "Algorithm: GEMM Simple" << endl;
    cout << "Result matrix" << endl;
    print_matrix(C, M, N);
    cout << "Execution time: " << duration << " ms\n\n";
}

// Function to run blocking matrix multiplication
void run_blocking_GEMM(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& D, int M, int K, int N){
    auto start = chrono::high_resolution_clock::now(); // start timer for blocking GEMM
    blocking_GEMM(A, B, D, M, K, N, BLOCK_SIZE);
    auto stop = chrono::high_resolution_clock::now(); // end timer for blocking GEMM

    auto duration = chrono::duration<double, milli>(stop-start).count();

    cout << "Algorithm: GEMM Blocking" << endl;
    cout << "Result matrix" << endl;
    print_matrix(D, M, N);
    cout << "Execution time: " << duration << " ms\n\n";
}

// Function to check if two matrices are equal
bool are_matrices_equal(vector<vector<int>>& A, vector<vector<int>>& B, int M, int N){
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            if(A[i][j]!=B[i][j])
                return false;
        }
    }
    return true;
}

// Main function to run matrix multiplication
void run_matrix_multiplication(){
    int M, K, N; // matrix dimensions
    vector<vector<int>> A, B; // matrices
    string filename; // input filename

    cout << "Enter input filename: ";
    cin >> filename;
    
    if(!read_matrices(filename, A, B, M, K, N)){
        cout << "Error reading matrices from file: " << filename << endl;
        return;
    }
    
    vector<vector<int>> C(M, vector<int> (N, 0));
    vector<vector<int>> D(M, vector<int> (N, 0));

    run_simple_GEMM(A, B, C, M, K, N);
    run_blocking_GEMM(A, B, D, M, K, N);

    if(are_matrices_equal(C, D, M, N))
        cout << "Both implementations produce the same result.\n";
    else
        cout << "Results do not match.\n";
}