#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "../../assignment_01/headers/csr_graph_creation.h"

bool bellman_ford(int source, CSRGraph& graph, int V, vector<int>& distance);
void run_bellman_ford_test();

#endif