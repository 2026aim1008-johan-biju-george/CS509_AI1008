#include "../headers/graph_generator.h"
#include "../headers/csr_graph_creation.h"
#include "../headers/kruskal.h"
#include "../headers/prim.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    srand(time(0));
    int choice;
    do{
        cout << "Assignment 2:\n";
        cout << "1. Generate MST Test Files\n";
        cout << "2. Run Prims Algorithm\n";
        cout << "3. Run Kruskals Algorithm\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                generate_weighted_tests();
                break;

            case 2:
                run_prim_test();
                break;

            case 3:
                run_kruskal_test();
                break;

            case 0:
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }while(choice != 0);
    return 0;
}