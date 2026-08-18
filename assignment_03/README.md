# Assignment 3 - Minimum Spanning Tree Algorithms (Prim and Kruskal)

## Assignment Details

**Type:** Single

**Objective:** The objective of the assignment is to implement two Minimum Spanning Tree (MST) algorithms:

- Prim's Algorithm
- Kruskal's Algorithm

Both algorithms are implemented for weighted, undirected and connected graphs.

The input graph is initially provided as an adjacency list. Before either MST algorithm is called, the graph is converted into Compressed Sparse Row (CSR) format using the CSR conversion function from the previous assignment.

Both algorithms are run on the same graph inputs so that their MST weights and execution times can be compared.

The required MST graph sizes are:

- 10 vertices
- 100 vertices
- 10,000 vertices
- 50,000 vertices
- 100,000 vertices

Large graphs are kept sparse, with approximately 2V to 4V edges where practical.

---

## Algorithms

### Prim's

It is a greedy algorithm that constructs an MST by starting from a selected vertex and repeatedly selecting the **minimum-weight** edge that connects a vertex already included in the MST to a vertex outside the MST.

In this implementation, vertex `0` is used as the starting vertex.

A min-priority queue is used to efficiently select the minimum-weight edge.

The algorithm works directly on the CSR representation of the graph.

Steps:

1. Start from vertex `0`.
2. Mark the starting vertex as visited.
3. Insert all edges from the starting vertex into the min-priority queue.
4. Select the minimum-weight edge from the priority queue.
5. If the destination vertex has not been visited:
   - Add the edge to the MST.
   - Add its weight to the total MST weight.
   - Mark the destination vertex as visited.
   - Insert its unvisited neighbouring edges into the priority queue.
6. Repeat until all vertices are included in the MST.

The MST contains exactly `V - 1` edges.

---

### Kruskal's

It is a greedy algorithm that considers graph edges in **non-decreasing** order of weight.

The implementation extracts the undirected edges from the CSR representation and stores each edge in the form: `{weight, u, v}`.

The edges are then sorted using the default `sort()` function.

A Disjoint Set Union (DSU) structure with path compression and union by size is used to detect cycles.

Steps:

1. Extract the unique undirected edges from the CSR representation.
2. Sort all edges in non-decreasing order of weight.
3. Initialize a Disjoint Set Union structure.
4. Process each edge in sorted order.
5. If the two endpoints belong to different components:
   * Add the edge to the MST.
   * Add its weight to the total MST weight.
   * Union the two components.
6. Stop when `V - 1` edges have been selected.

---

## Input Format

The input graph is a weighted, undirected adjacency list.

The format is:

```
V E
u0 degree neighbor1 weight1 neighbor2 weight2 ...
u1 degree neighbor1 weight1 neighbor2 weight2 ...
...
u(V-1) degree neighbor1 weight1 neighbor2 weight2 ...
```

Where:

* `V` = number of vertices.
* `E` = number of undirected edges.
* `u` = vertex number.
* `degree` = number of neighbours of the vertex.
* Each neighbour is followed by its edge weight.

Vertex numbering starts from `0` and continues up to `V - 1`.

Since the graph is undirected, every edge is present in the adjacency lists of both endpoints with the same weight.

For example, an edge:

```
0 1 5
```

means that there is an undirected edge between vertices `0` and `1` with weight `5`.

The edge is therefore represented in both adjacency lists:

```
0 ... 1 5 ...
1 ... 0 5 ...
```

`E` counts each undirected edge only once.

Example:

```
5 7
0 2 1 2 3 6
1 4 0 2 2 3 3 8 4 5
2 2 1 3 4 7
3 3 0 6 1 8 4 9
4 3 1 5 2 7 3 9
```

---

## Assumptions and Constraints

* The graph is weighted, undirected and connected.
* Vertex numbering is from `0` to `V - 1`.
* Every undirected edge appears in the adjacency list of both endpoint vertices.
* The same edge weight is used in both directions.
* `E` counts each undirected edge only once.
* The graph must be connected.
* A valid MST contains exactly `V - 1` edges.
* Both Prim's and Kruskal's algorithms use the same input graph.
* The adjacency-list representation is converted to CSR before running the algorithms.
* CSR conversion is considered preprocessing and is not included in algorithm execution time.
* For Kruskal's Algorithm, CSR edge extraction and edge sorting are part of the algorithm execution and are included in its measured time.
* Prim's Algorithm starts from vertex `0`.
* Kruskal's Algorithm uses DSU/Union-Find to detect cycles.
* Prim's Algorithm uses a min-priority queue.
* Edge weights may be positive, zero, or negative integers.
* The total MST weight produced by Prim's and Kruskal's must be equal.
* If multiple MSTs exist, the selected edge sets may differ as long as their total weights are equal and minimum.

---

## Driver File, Source Files, Header Files, Helper Functions and Test Files

### Driver File

#### `driver/driver.cpp`

Provides the menu-driven interface for Assignment 3.

The menu provides options to:

```
1. Generate MST Test Files
2. Run Prim's Algorithm
3. Run Kruskal's Algorithm
0. Exit
```

The driver:

1. Accepts the input filename.
2. Reads the weighted graph.
3. Converts the adjacency list into CSR format.
4. Calls the selected MST algorithm.
5. Prints the MST edges, total MST weight and execution time.

---

### Source Files

#### `src/kruskal.cpp`

Implements Kruskal's Minimum Spanning Tree algorithm.

Main functions include:

```
kruskal_MST()
run_kruskal()
run_kruskal_test()
```

`kruskal_MST()` performs the actual MST computation using:

* CSR graph representation
* Edge extraction
* Edge sorting
* Disjoint Set Union
* Union by size
* Path compression

`run_kruskal()` measures the execution time of the Kruskal algorithm and prints the result.

`run_prim_test()` takes the filename as input, reads the graph from file and runs Kruskal's algorithm.

---

#### `src/prim.cpp`

Implements Prim's Minimum Spanning Tree algorithm.

Main functions include:

```
prim_MST()
run_prim()
run_prim_test()
```

`prim_MST()` performs the actual MST computation using:

* CSR graph representation
* Visited vertices
* Min-priority queue

`run_prim()` measures the execution time of the Prim algorithm and prints the result.

`run_prim_test()` takes the filename as input, reads the graph from file and runs Prim's algorithm.

---

#### `src/csr_graph_creation.cpp`

Contains functions for reading weighted graph input files and converting the adjacency-list representation into CSR format.

Main functions include:

```
read_weighted_graph()
convert_weighted_graph_to_CSR()
```

The CSR representation contains:

```
row_ptr
col_idx
values
```

where:

* `row_ptr` stores the starting and ending positions of each vertex's adjacency list.
* `col_idx` stores neighbouring vertex numbers.
* `values` stores edge weights.

CSR conversion is performed before timing the MST algorithms.

---

#### `src/generate_weighted_graph.cpp`

Generates weighted, undirected and connected graphs for MST testing.

The generated graphs contain the required number of vertices and edges.

The generator creates a connected graph first and then adds additional random edges until the requested number of edges is reached.

---

### Header Files

#### `headers/csr_graph_creation.h`

Contains declarations for CSR graph structures and functions for reading weighted graphs and converting them into CSR format.

---

#### `headers/graph_generator.h`

Contains declarations for functions that generate weighted MST test graphs.

---

#### `headers/kruskal.h`

Contains declarations for Kruskal's algorithm functions.

---

#### `headers/prim.h`

Contains declarations for Prim's algorithm functions.

---

### Test Files

#### MST

```
tests/mst_10.txt
tests/mst_100.txt
tests/mst_10000.txt
tests/mst_50000.txt
tests/mst_100000.txt
```

The same test files are used for both Prim's and Kruskal's algorithms.

---

## 6. Compilation

The program is compiled using `g++`.

From the root directory (where all assignment folders are located):

```
g++ assignment_03/driver/driver.cpp assignment_03/src/*.cpp -o assignment_03/assignment3.exe
```

---

## 7. Execution

Run the program from the `assignment_03` directory.

### Windows

```
assignment3.exe
```

### Linux

```
./assignment3
```

The program displays:

```
Assignment 3:
1. Generate MST Test Files
2. Run Prim's Algorithm
3. Run Kruskal's Algorithm
0. Exit
```

---

## 8. Execution Steps

### 1. Generate MST Test Files

* Select **1**.
* This generates the required MST test files:

```
mst_10.txt
mst_100.txt
mst_10000.txt
mst_50000.txt
mst_100000.txt
```

The generated graphs are weighted, undirected and connected.

---

### 2. Run Prim's

* Select **2**.
* Enter the required input filename, for example: `tests/mst_10.txt`.
* The program reads the graph.
* The adjacency list is converted to CSR.
* Prim's Algorithm is executed.
* The MST edges, total MST weight and execution time are displayed.

---

### 3. Run Kruskal's

* Select **3**.
* Enter the required input filename, for example: `tests/mst_10.txt`.
* The program reads the graph.
* The adjacency list is converted to CSR.
* Kruskal's Algorithm is executed.
* The MST edges, total MST weight and execution time are displayed.

---

### 4. Compare Prim's and Kruskal's

Both algorithms should be run using the same input file.

Their total MST weights are compared.

The result is considered correct when:

```
Kruskal Weight == Prim Weight
```

The edge lists may differ when multiple valid MSTs exist.

---

## 9. Performance Measurement

Only the **execution time of the MST algorithm** is measured.

The following operations are not included in the reported time:

* File reading
* Input parsing
* Adjacency-list construction
* CSR conversion
* Result printing
* File writing

Execution time is reported in milliseconds.

For Kruskal's Algorithm, the following operations are included in the measured time:

* Extracting the edge list from the prepared CSR representation
* Sorting the edges
* DSU operations
* MST construction

The timer starts immediately before the MST algorithm is called and stops immediately after it finishes.

---

## Expected and Actual Outputs

### Prim's

Expected output format:

```text
Algorithm: Prim's MST
MST edges:
0 1 2
1 2 3
1 4 5
0 3 6
Total MST weight: 16
Execution time: <value> ms
```

---

### Kruskal's

Expected output format:

```text
Algorithm: Kruskal's MST
MST edges:
0 1 2
1 2 3
1 4 5
0 3 6
Total MST weight: 16
Execution time: <value> ms
```

The exact edge order may differ between the two algorithms when multiple MSTs are possible.

The total MST weight must be the same for both algorithms.

---

## Results

### MST Results

| File             |      V |      E | Expected Weight | Kruskal Weight | Prim Weight | Kruskal Time (ms) | Prim Time (ms) | Equal? | Status |
| ---------------- | -----: | -----: | --------------: | -------------: | ----------: | ----------------: | -------------: | ------ | ------ |
| `mst_10.txt`     |     10 |     20 |              23 |             23 |          23 |            0.0626 |          0.082 | Yes    | Pass   |
| `mst_100.txt`    |    100 |    200 |             319 |            319 |         319 |            0.2647 |         0.7487 | Yes    | Pass   |
| `mst_10000.txt`  |  10000 |  20000 |           33989 |          33989 |       33989 |           44.1863 |        52.5969 | Yes    | Pass   |
| `mst_50000.txt`  |  50000 | 100000 |          187685 |         187685 |      187685 |           116.921 |        179.311 | Yes    | Pass   |
| `mst_100000.txt` | 100000 | 200000 |          434319 |         434319 |      434319 |           216.434 |        424.662 | Yes    | Pass   |

---

## Performance Analysis

For the tested graphs, both Prim's and Kruskal's algorithms produce the **same** total MST weight, confirming the correctness of the implementations.

As the graph size increases, the execution time of both algorithms **increases**.

Kruskal's Algorithm performs edge extraction and sorting, so its performance is strongly affected by the **number of edges**.

Prim's Algorithm uses a **min-priority queue** and repeatedly selects the **minimum-weight edge** that connects the current MST to an unvisited vertex.

For the tested sparse graphs, the **measured execution times** can be compared to determine which implementation performs better on the given hardware and graph characteristics.

The actual performance depends on:

* Number of vertices `V`
* Number of edges `E`
* Graph sparsity
* Edge-weight distribution
* Priority queue operations
* Edge sorting
* DSU operations
* Hardware and compiler optimization settings

---

## Complexity

### Prim's

Using a min-priority queue and CSR representation, Prim's Algorithm has a typical time complexity of **O(E log E)** for the implementation using a priority queue of edges.

For sparse graphs where `E` is proportional to `V`, this is approximately **O(V log V)**.

The CSR representation requires **O(V + E)** space, while the visited array and priority queue require additional space.

---

### Kruskal's

Kruskal's Algorithm performs the following major operations:

1. Extract edges from CSR: **O(E)**
2. Sort edges: **O(E log E)**
3. DSU operations: approximately **O(E α(V))**

Therefore, the overall time complexity is **O(E log E)** because edge sorting dominates the DSU operations.

The CSR representation requires **O(V + E)** space, while the extracted edge list and DSU structure require additional space.

---

## References

1. Cormen, Leiserson, Rivest and Stein, *Introduction to Algorithms*.
2. Princeton Algorithms, Section 4.3 - Minimum Spanning Trees:
   [https://algs4.cs.princeton.edu/43mst/](https://algs4.cs.princeton.edu/43mst/)

---
