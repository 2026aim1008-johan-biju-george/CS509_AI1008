# Assignment 3 - Minimum Spanning Tree Algorithms (Prim and Kruskal)

## Assignment Details

---

## Algorithms

### Prim's


---

### Kruskal's



---

## Input Format


---

## Assumptions and Constraints

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

#### `src/kruskal.cpp`

Main functions include:
```
read_weighted_graph()
kruskal_MST()
run_kruskal()
run_kruskal_test()
```

---

#### `src/prim.cpp`

Main functions include:

```
prim_MST()
run_prim()
run_prim_test()
```

---

#### `src/generate_weighted_graph.cpp`

Generates weighted directed graphs for MST.

---

### Header Files

#### `headers/csr_graph_creation.h`

Contains declarations for CSR conversion function as well as the function for reading weighted graphs.

#### `headers/graph_generator.h`

Contains declarations for functions which generate weighted graphs.

#### `headers/kruskal.h`

Contains declarations for Kruskal's algorithm functions.

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

---

## 6. Compilation

The program is compiled using `g++`.

From the root directory (where the common wrapper file is located):

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
Assignment 2:
1. Generate MST Test Files
2. Run Prims Algorithm
3. Run Kruskals Algorithm
0. Exit
```

---

## 8. Execution Steps

1. Generate MST Test Files

- Select **1**.
- This generates the test files:

```
mst_10.txt
mst_100.txt
mst_10000.txt
mst_50000.txt
mst_100000.txt
```

---

2. Run Prim's

- Select **3**.
- Enter the required input filename, for example, `tests/mst_10.txt`.
- The program reads the graph, converts it to CSR and runs Prim's.

---

3. Run Kruskal's

- Select **3**.
- Enter the required input filename, for example, `tests/mst_10.txt`.
- The program reads the graph, converts it to CSR and runs Prim's.

---

## 9. Performance Measurement

Only the **execution time** of the algorithm is measured.

The following operations are not included in the reported time:

* File reading
* Input parsing
* CSR conversion
* Output printing
* File writing

Execution time is reported in milliseconds.

---

## Expected and Actual Outputs

### Prim's

Expected output format:

```
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

```
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

## Results

### MST Results

| File       | V | E | Expected Weight | Kruskal Weight | Prim Weight | Kruskal Time (ms)  | Prim Time (ms)  | Equal? | Status |
| --------- | -- | ---: | --------: | ----------------- | :-----------: | ---------------- | --------------- | ------ | -----: |
| `mst_10.txt`      |   10 |  20 |  23   |  23  | 23   |   0.0626    |  0.082     |   Yes    |  Pass  |
| `mst_100.txt`      |  100 | 200 |  319      |  319     |   319  |  0.2647       | 0.7487     |  Yes   |  Pass  |
| `mst_10000.txt`     |  10000 | 20000 | 33989 | 33989  | 33989   | 44.1863 | 52.5969  |  Yes  |  Pass  |
| `mst_50000.txt`     |  50000 | 100000 | 187685  | 187685  | 187685   | 116.921      | 179.311    | Yes   |  Pass  |
| `mst_100000.txt`     | 100000 | 200000 | 434319 | 434319  | 434319  | 216.434  | 424.662   | Yes  |  Pass  |

---

---

## Performance Analysis


---

## Complexity

### Prim's


---

### Kruskal's


---

## References

1. Cormen, Leiserson, Rivest and Stein, *Introduction to Algorithms*.

---
