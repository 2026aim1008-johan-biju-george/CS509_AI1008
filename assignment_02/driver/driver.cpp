#include "../headers/bellman_ford.h"
#include "../headers/floyd_warshall.h"
#include "../headers/graph_generator.h"
#include "../headers/distance_matrix_generator.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    srand(time(0));
    int choice;
    do{
        cout << "Assignment 2:\n";
        cout << "1. Generate Bellman-Ford Test Files\n";
        cout << "2. Generate Floyd-Warshall Test Files\n";
        cout << "3. Run Bellman-Ford Algorithm\n";
        cout << "4. Run Floyd-Warshall Algorithm\n";
        cout << "5. Cross-check Bellman-Ford and Floyd-Warshall\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                generate_weighted_tests();
                break;

            case 2:
                generate_distance_matrix_tests();
                break;

            case 3:
                run_bellman_ford_test();
                break;

            case 4:
                run_floyd_warshall_test();
                break;
                
            case 5:
                run_cross_checks();
                break;
            case 0:
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }while(choice != 0);
    return 0;
}