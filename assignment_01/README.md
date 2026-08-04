# Assignment 1: General Matrix Multiplication (GEMM)

## Assignment Details

**Type:** Single

**Objective:**
The objective of this assignment is to implement and compare two matrix multiplication algorithms:

1. Simple (naive) General Matrix Multiplication (GEMM)
2. Blocked (Tiled) General Matrix Multiplication (GEMM)

The assignment evaluates the effect of cache-aware optimization using blocking and measures the execution time of both implementations for matrices of different sizes.

---

## Algorithms

### 1. Simple GEMM

The simple GEMM algorithm performs matrix multiplication using three nested loops.

For every element `C[i][j]`, the algorithm computes:

* Iterate through every row of matrix **A**.
* Iterate through every column of matrix **B**.
* Compute the dot product of the corresponding row and column.

This approach has poor cache locality because elements of matrix **B** are accessed column-wise.

---

### 2. Blocked GEMM

Blocked GEMM divides the matrices into smaller submatrices (blocks/tiles).

Instead of processing the entire matrices at once, multiplication is performed block by block.

Advantages:

* Better cache utilization
* Reduced cache misses
* Improved performance for large matrices

The implementation uses a configurable block size and processes matrices using six nested loops.

---

## Input Format

The program reads matrices from text files.

Each input file contains:

* Matrix dimensions `M K N`
* Matrix **A** of size `M × K`
* Matrix **B** of size `K × N`

Matrices contain integer values.

---

## Assumptions and Constraints

* Matrix multiplication is valid (`A` columns = `B` rows).
* Matrix elements are integers.
* Input files are correctly formatted.
* Output matrix size is `M × N`.
* Block size can be modified by changing the `BLOCK_SIZE` macro.

---

## Description of Source Files, Driver Files, Helper Functions, and Test Files

### Driver File (stored in `driver/`)

| File       | Description                                                                                                                                                                                                                                                                      |
| ---------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `driver.cpp` | Menu-driven driver program that serves as the entry point of the application. It allows the user to generate matrix test cases, perform matrix multiplication, generate graph test cases, and create CSR representations of graphs by invoking the appropriate module functions. |

### Source Files (stored in `src/`)

| File                        | Description                                                                                                                                     |
| --------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------- |
| `matrix_generator.cpp`      | Generates random matrix test cases of different dimensions and stores them in input files.                                                      |
| `matrix_multiplication.cpp` | Implements both the Simple GEMM and Blocked GEMM algorithms, executes matrix multiplication, measures execution time, and verifies the results. |
| `generate_unweighted_graph.cpp`  | Generates unweighted graph test cases with varying numbers of vertices and edges.                                                         |
| `generate_weighted_graph.cpp`  | Generates weighted graph test cases with varying numbers of vertices and edges.                                                         |
| `csr_graph_creation.cpp`    | Reads graph input files, constructs the Compressed Sparse Row (CSR) representation, and displays or stores the CSR arrays.                      |

### Header Files (stored in `headers/`)

| File                      | Description                                                                               |
| ------------------------- | ----------------------------------------------------------------------------------------- |
| `matrix_generator.h`      | Function declarations related to matrix test generation.                                  |
| `matrix_multiplication.h` | Function declarations for Simple GEMM, Blocked GEMM, and matrix multiplication utilities. |
| `graph_generator.h`       | Function declarations for weighted and unweighted graph generation.                       |
| `csr_graph_creation.h`    | Function declarations for CSR graph construction and related operations.                  |

### Helper Functions

| Function                      | Description                                                                              |
| ----------------------------- | ---------------------------------------------------------------------------------------- |
| `generate_matrix_tests()`     | Generates matrix input files of different dimensions.                                    |
| `run_matrix_multiplication()` | Reads matrix test cases, executes both GEMM implementations, and reports execution time. |
| `generate_unweighted_tests()` | Generates random unweighted graph test cases.                                            |
| `generate_weighted_tests()`   | Generates random weighted graph test cases.                                              |
| `run_csr_graph()`             | Reads graph test cases and generates the corresponding CSR representation.               |

### Test Files (stored in `tests/`)

| Directory/File    | Description                                                                                                          |
| ----------------- | -------------------------------------------------------------------------------------------------------------------- |
| `gemm_test_xx.txt` | Contains matrix dimensions followed by the elements of matrices A and B.                                              |
| `graph_xx.txt` | Contains the number of vertices, number of edges, and the adjacency list (weighted or unweighted) used for CSR generation. |


## Compilation

Compilation is done using g++ with `-O1` optimization enabled:

```
g++ -O1 driver/driver.cpp src/*.cpp -o assignment1.exe
```

---

## Execution

```
./assignment1
```

---

## Test Cases

The following matrix dimensions were tested:

| Test Case | Matrix Dimensions |
| --------- | ----------------- |
| 1         | 4 × 4             |
| 2         | 16 × 16           |
| 3         | 32 × 32           |
| 4         | 64 × 64           |
| 5         | 128 × 128         |
| 6         | 256 × 256         |
| 7         | 512 × 512         |

---

## Expected and Actual Outputs

For every test case:
* Matrix multiplication is performed correctly.
* Both algorithms produce identical output matrices.
* Execution time of both algorithms is displayed.

Example:

```
===== Test Case 6 =====
Matrix Dimensions: 256 x 256

Simple GEMM Execution Time : 58.2455 ms
Blocked GEMM Execution Time : 39.4184 ms

Outputs Match : Yes
```

---

## Results

### GEMM

| Test File | Matrix Size | Expected Output | Actual Output | Simple Time (ms) | Blocking Time (ms) | Block Size | Status |
|-----------|-------------|----------------|---------------|-----------------:|-------------------:|-----------:|--------|
| `gemm_test_01.txt` | 4×4 and 4x4 | Result matrix | Same as Result matrix | 0.000304 | 0.000308 | 16 | Pass |
| `gemm_test_02.txt` | 16×16 and 16x16 | Result matrix | Same as Result matrix | 0.016721 | 0.009004 | 16 | Pass |
| `gemm_test_03.txt` | 32×32 and 32x32 | Result matrix | Same as Result matrix | 0.143815 | 0.06939 | 16 | Pass |
| `gemm_test_04.txt` | 64×64 and 64x64 | Result matrix | Same as Result matrix | 0.970061 | 0.587555 | 16 | Pass |
| `gemm_test_05.txt` | 128×128 and 128x128 | Result matrix | Same as Result matrix | 7.2933 | 4.3899 | 16 | Pass |
| `gemm_test_06.txt` | 256×256 and 256x256 | Result matrix | Same as Result matrix | 58.2455 | 39.4184 | 16 | Pass |
| `gemm_test_07.txt` | 512×512 and 512x512 | Result matrix | Same as Result matrix | 334.142 | 302.575 | 16 | Pass |

---

## Performance Analysis

Execution time was measured using the C++ `chrono::high_resolution_clock`.

Assuming that matrix sizes <= 64 are considered 'fast inputs', in that case we take the average execution time over 100 runs. Otherwise we take only the execution time only for a single run.

Compilation was performed using:

```
g++ -O1
```

Blocked GEMM provides improved cache performance for larger matrices, resulting in lower execution time compared to the simple implementation.

---

## Time Complexity

### Simple GEMM

* **Time Complexity:** O(M × N × K)
* **Space Complexity:** O(M × N) (excluding input matrices)

### Blocked GEMM

* **Time Complexity:** O(M × N × K)
* **Space Complexity:** O(M × N)

Although both algorithms have the same asymptotic complexity, blocked GEMM generally performs better due to improved cache locality.

---

## References

1. Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. *Introduction to Algorithms (CLRS)*.
2. [Intel Developer Documentation on Cache Optimization](https://cdrdv2-public.intel.com/821613/355308-Optimization-Reference-Manual-050-Changes-Doc.pdf).
3. [GCC Documentation for Compiler Optimization](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html).
