# Assignment 2 - Shortest Path Algorithms (Bellman-Ford and Floyd-Warshall)

## Assignment Details

**Type:** Single

**Objective:** The objective of this assignment is to implement two shortest-path algorithms:

1. **Bellman-Ford**
   - Single-source shortest path algorithm.
   - Supports directed graphs with negative edge weights.
   - Detects negative-weight cycles reachable from the selected source.

2. **Floyd-Warshall**
   - All-pairs shortest path algorithm.
   - Computes the shortest distance between every pair of vertices.
   - Supports negative edge weights as long as there is no negative-weight cycle.

The assignment uses **CSR (Compressed Sparse Row)** representation for Bellman-Ford. The CSR conversion function from Assignment 1 is **reused** instead of being copied into this assignment.

Floyd-Warshall directly uses a **dense distance matrix**.

---

## Algorithms

### Bellman-Ford

It computes the shortest distance from one source vertex to every other reachable vertex.

The algorithm:

1. Initializes the source distance to `0` and all other distances to `INF`.
2. Relaxes all edges `V-1` times.
3. Performs one additional relaxation pass.
4. If an edge can still be relaxed, a negative-weight cycle reachable from the source exists.

The implementation works with negative edge weights.

---

### Floyd-Warshall

It computes shortest paths between every pair of vertices.

For every intermediate vertex `k`, the algorithm checks whether the path from `i` to `j` can be improved by going through `k`.

The update is:

```
distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j])
```

After the algorithm finishes, a negative value on any diagonal entry `distance[i][i]` indicates a negative-weight cycle.

Because of its cubic time and quadratic memory requirements, Floyd-Warshall is tested only for 10, 100, 500, 1000, 2000 vertices.

---

## Input Format

### Bellman-Ford Input

Bellman-Ford uses a directed weighted adjacency-list format.

```
V E
u0 degree neighbor1 weight1 neighbor2 weight2 ...
u1 degree neighbor1 weight1 neighbor2 weight2 ...
...
u(V-1) degree neighbor1 weight1 ...
SOURCE s
```

Example:

```
5 10
0 2 1 6 3 7
1 3 2 5 3 8 4 -4
2 1 1 -2
3 2 2 -3 4 9
4 2 0 2 2 7
SOURCE 0
```

Vertices are numbered from `0` to `V-1`.

The graph is directed and edge weights may be negative.

---

### Floyd-Warshall Input

Floyd-Warshall uses a dense distance matrix.

The format is:

```
V
row 0
row 1
...
row V-1
```

Each row contains exactly `V` entries.

An entry is either:

* an integer edge weight, or
* `INF` if there is no direct edge.

The diagonal entries are always `0`.

Example:

```
5
0 3 8 INF -4
INF 0 INF 1 7
INF 4 0 INF INF
2 INF -5 0 INF
INF INF INF 6 0
```

---

## Assumptions and Constraints

* Vertices are numbered from `0` to `V-1`.
* Bellman-Ford graphs are directed.
* Floyd-Warshall input represents a directed weighted graph.
* Negative edge weights are allowed for both algorithms.
* A negative-weight edge must not be placed on an undirected edge.
* `INF` represents the absence of a direct edge.
* Diagonal entries in Floyd-Warshall input are `0`.
* Every test case is stored in a separate `.txt` file.
* CSR conversion is performed before timing Bellman-Ford.
* File reading, input parsing, CSR conversion and output printing are excluded from algorithm execution time.

---

## Driver File, Source Files, Header Files, Helper Functions and Test Files

### Driver File

#### `driver/driver.cpp`

Provides the menu-driven interface for Assignment 2.

The menu provides options to:

```
1. Generate Bellman-Ford Test Files
2. Generate Floyd-Warshall Test Files
3. Run Bellman-Ford Algorithm
4. Run Floyd-Warshall Algorithm
0. Exit
```

### Source Files

#### `src/bellman_ford.cpp`

Contains the Bellman-Ford implementation and functions related to:

* Reading weighted adjacency-list input.
* Running Bellman-Ford.
* Detecting negative-weight cycles.
* Running Bellman-Ford test cases.

Main functions include:

```
read_weighted_graph()
bellman_ford()
run_bellman_ford()
run_bellman_ford_test()
```

---

#### `src/floyd_warshall.cpp`

Contains the Floyd-Warshall implementation and functions related to:

* Reading the distance matrix.
* Running Floyd-Warshall.
* Detecting negative-weight cycles.
* Cross-checking Bellman-Ford and Floyd-Warshall.
* Running Floyd-Warshall test cases.

Main functions include:

```
read_distance_matrix()
floyd_warshall()
has_negative_cycle()
run_floyd_warshall()
run_floyd_warshall_test()
cross_check()
run_cross_checks()
```

The cross-check runs Bellman-Ford from every vertex and compares its results with the corresponding row of the Floyd-Warshall distance matrix for the 10-vertex and 100-vertex test cases.

---

#### `src/generate_weighted_graph.cpp`

Generates weighted directed graphs for Bellman-Ford. It allows control over the percentage of negative edges.

For example, `generate_weighted_graph("bf", 100, 200, 0, true, 0.20)` generates a graph with approximately 20% negative edges.

---

#### `src/distance_matrix_generator.cpp`

Generates dense adjacency matrices for Floyd-Warshall.

The generated matrix:

* Contains `0` on the diagonal.
* Contains integer weights for existing edges.
* Contains `INF` for missing direct edges.
* Uses an edge probability to control how many direct edges are generated.

Generated files follow the required naming convention:

```
fw_10.txt
fw_100.txt
fw_500.txt
fw_1000.txt
fw_2000.txt
```

---

### Header Files

#### `headers/bellman_ford.h`

Contains declarations for Bellman-Ford functions.

#### `headers/floyd_warshall.h`

Contains declarations for Floyd-Warshall functions.

#### `headers/graph_generator.h`

Contains declarations for weighted graph generation functions.

#### `headers/distance_matrix_generator.h`

Contains declarations for Floyd-Warshall distance matrix generation functions.

The CSR graph structure and CSR conversion function are reused from Assignment 1.

---

### Test Files

#### Bellman-Ford

```
tests/bf_10.txt
tests/bf_100.txt
tests/bf_10000.txt
tests/bf_50000.txt
tests/bf_100000.txt
```

#### Floyd-Warshall

```
tests/fw_10.txt
tests/fw_100.txt
tests/fw_500.txt
tests/fw_1000.txt
tests/fw_2000.txt
```

The required graph sizes follow the assignment specification. Bellman-Ford uses the full range up to 100,000 vertices, while Floyd-Warshall uses the reduced range because of its cubic time and quadratic memory requirements.

---

## 6. Compilation

The program is compiled using `g++`.

From the root directory (where the common wrapper file is located):

```
g++ assignment_02/driver/driver.cpp assignment_02/src/*.cpp assignment_01/src/csr_graph_creation.cpp -o assignment_02/assignment2.exe
```

The program also depends on the CSR implementation from Assignment 1.

---

## 7. Execution

Run the program from the `assignment_02` directory.

### Windows

```
assignment2.exe
```

### Linux

```
./assignment2
```

The program displays:

```
Assignment 2:
1. Generate Bellman-Ford Test Files
2. Generate Floyd-Warshall Test Files
3. Run Bellman-Ford Algorithm
4. Run Floyd-Warshall Algorithm
0. Exit
```

---

## 8. Execution Steps

1. Generate Bellman-Ford Test Files

- Select **1**.
- This generates the test files:

```
bf_10.txt
bf_100.txt
bf_10000.txt
bf_50000.txt
bf_100000.txt
```

---

2. Generate Floyd-Warshall Test Files

- Select **2**.
- This generates the test files:

```
fw_10.txt
fw_100.txt
fw_500.txt
fw_1000.txt
fw_2000.txt
```

---

3. Run Bellman-Ford

- Select **3**.
- Enter the required input filename, for example, `tests/bf_10.txt`.
- The program reads the graph, converts it to CSR and runs Bellman-Ford.

---

4. Run Floyd-Warshall

- Select **4**.
- Enter the required input filename, for example, `tests/fw_10.txt`.
- The program reads the matrix and runs Floyd-Warshall.

---

5. Run the Cross-Check

For the common graph sizes:

```
10 vertices
100 vertices
```

Bellman-Ford is run once from every vertex.

Each Bellman-Ford result is compared with the corresponding row of the Floyd-Warshall result.

The expected output is:

```
Cross-checking graph of 10 vertices
Cross-check passed for V = 10

Cross-checking graph of 100 vertices
Cross-check passed for V = 100
```

This confirms that both algorithms produce the same shortest-path distances for the common test graphs.

---

## 9. Performance Measurement

Only the **execution time** of the algorithm is measured.

For Bellman-Ford, the timer starts immediately before `bellman_ford(...)` and stops immediately after it finishes, including the negative-cycle detection pass.

CSR conversion is performed before starting the timer.

For Floyd-Warshall, the timer starts immediately before `floyd_warshall(...)` and stops after Floyd-Warshall and the negative-cycle check finish.

The following operations are not included in the reported time:

* File reading
* Input parsing
* CSR conversion
* Matrix construction
* Output printing
* File writing

Execution time is reported in milliseconds.

---

## Expected and Actual Outputs

### Bellman-Ford

Expected output format:

```
Algorithm: Bellman-Ford
Source: 0
Vertex Distance
0 0
1 2
2 4
3 7
4 -2
Negative cycle: none
Execution time: <value> ms
```

For a negative-cycle test case:

```
Algorithm: Bellman-Ford
Source: 0
Negative cycle: true
Execution time: <value> ms
```

The distance table is omitted when a negative cycle is detected.

---

### Floyd-Warshall

Expected output format:

```
Algorithm: Floyd-Warshall
Distance matrix:
0 1 -3 2 -4
3 0 -4 1 -1
7 4 0 5 3
2 -1 -5 0 -2
8 5 1 6 0
Negative cycle: none
Execution time: <value> ms
```

For larger matrices, the program reports that the distance matrix was computed successfully instead of printing a very large matrix.

For a negative-cycle test case:

```text
Algorithm: Floyd-Warshall
Negative cycle: true
Execution time: <value> ms
```

---

## Results

### Test Results

| Algorithm | Test File         | Vertices (V) | Edges (E) | Input Type                       | Source Vertex | Negative Cycle | Expected Output            | Actual Output              | Execution Time (ms) | Status |
| --------- | ----------------- | -----------: | --------: | -------------------------------- | :-----------: | -------| -------------------------- | -------------------------- | ------------------: | :----: |
| Bellman-Ford       | `bf_10.txt`      |           10 |        20 | Weighted Adjacency List        |       0   |  No  | Distances        | Correct Distances        |   0.0124         |  Pass  |
| Floyd-Warshall       | `fw_10.txt`      |           10 |  N/A | Distance Matrix        |       N/A  | No     | Distance Matrix        | Correct Distance Matrix       |  0.0389          |  Pass  |
| Bellman-Ford      | `bf_100.txt`     |           100 |        200 | Weighted Adjacency List |       0   |  No  | Distances  | Correct Distances  |   0.5525            |  Pass  |
| Floyd-Warshall       | `fw_100.txt`     |          100 | N/A | Distance Matrix        |       N/A  |  No   | Distance Matrix        | Correct Distance Matrix        |  4.7746           |  Pass  |
| Bellman-Ford       | `bf_10000.txt`     |          10000 |       20000 | Weighted Adjacency List        |       0 |   Yes   | N/A         | N/A         |  5998.78           |  Fail  |
| Floyd-Warshall      | `fw_500.txt`    |          500 |  N/A | Distance Matrix |       N/A |  No    | Distance Matrix | Correct Distance Matrix |  3009.66             |  Pass  |
| Bellman-Ford       | `bf_50000.txt`   |        50000 |     100000 | Weighted Adjacency List        |       0 |  Yes  | N/A         | N/A        |   290953            |  Fail  |
| Floyd-Warshall       | `fw_1000.txt`   |        1000 |  N/A | Distance Matrix        |       N/A |  No    | Distance Matrix        | Correct Distance Matrix        |  28013.1        |  Pass  |
| Bellman-Ford      | `bf_100000.txt`  |        100000 |     200000 | Weighted Adjacency List |       0 |   Yes   | N/A | N/A  |  941781            |  Pass  |
| Floyd-Warshall       | `fw_2000.txt`   |        2000 |  N/A | Distance Matrix        |       N/A   |  No | Distance Matrix  | Correct Distance Matrix        |    143179         |  Pass  |

---

### Cross-Check Results

| Vertices | Bellman-Ford Sources | Floyd-Warshall | Result |
| ------- | ------------------- | -------------- | ------ |
|       10 |      All 10 vertices | All-pairs      | Pass   |
|      100 |     All 100 vertices | All-pairs      | Pass   |

The cross-check passed for both common graph sizes.

---

## Performance Analysis

Bellman-Ford has a time complexity of `O(V x E)`. Therefore, its execution time increases significantly as both the number of vertices and edges increase.

The measured execution times show this increase:

* `V = 10`: approximately `0.0124 ms`
* `V = 100`: approximately `0.5525 ms`
* `V = 10000`: approximately `5998.78 ms`
* `V = 50000`: approximately `290953 ms`
* `V = 100000`: approximately `941781 ms`

The large increase is expected because Bellman-Ford repeatedly relaxes all edges.

The two largest Bellman-Ford graphs are kept relatively sparse so that the `O(V x E)` computation remains practical.

Floyd-Warshall has `O(V^3)` time complexity. Consequently, increasing the number of vertices has a much stronger effect on execution time.

For example:

```
500 vertices   -> 500^3 operations
1000 vertices  -> 1000^3 operations
2000 vertices  -> 2000^3 operations
```

Thus, increasing the number of vertices from 1000 to 2000 increases the cubic workload by approximately a factor of 8.

Floyd-Warshall is therefore tested only up to 2000 vertices.

---

## Complexity

### Bellman-Ford

* **Time Complexity:** O(V x E)
* **Space Complexity:** O(V + E)

The graph is stored using CSR, which provides compact storage for sparse graphs.

---

### Floyd-Warshall

* **Time Complexity:** O(V^3)
* **Space Complexity:** O(V^2)

The full `V x V` distance matrix is stored in memory.

---

## References

1. Cormen, Leiserson, Rivest and Stein, *Introduction to Algorithms*.
2. Bellman-Ford algorithm:
   [https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm)
3. Floyd-Warshall algorithm:
   [https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm)
4. Compressed Sparse Row (CSR) graph representation from Assignment 1.

---
