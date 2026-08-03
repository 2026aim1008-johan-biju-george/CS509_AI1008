#include "../headers/matrix_multiplication.h"
#include "../headers/csr_graph_creation.h"
#include "../headers/graph_generator.h"
#include "../headers/matrix_generator.h"
#include <iostream>

using namespace std;

int main(){
    srand(time(0));
    int choice;
    do{
        cout << "Assignment 1:\n";
        cout << "1. Generate Matrices\n";
        cout << "2. Matrix Multiplication\n";
        cout << "3. Generate Graph Test Files\n";
        cout << "4. CSR Graph Generation\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                generate_matrix_tests();
                break;

            case 2:
                run_matrix_multiplication();
                break;

            case 3:
                generate_unweighted_tests();
                generate_weighted_tests();
                break;

            case 4:
                run_csr_graph();
                break;

            case 0:
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }while(choice != 0);
    return 0;
}