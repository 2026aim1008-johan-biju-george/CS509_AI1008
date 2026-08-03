## Project Structure

```
assignment_01/
│
├── driver/
├── headers/
├── src/
├── tests/
├── assignment1.exe
└── README.md
```

## Features

- Simple GEMM
- Blocking GEMM
- Matrix test generation
- Graph test generation
- BFS
- DFS
- SSSP (Dijkstra's Algorithm)
- Performance benchmarking
- Common driver interface

## Compilation

The assignment was compiled using:

```
g++ -O1 driver/driver.cpp src/*.cpp -o assignment1.exe
```

## Execution

```
.\assignment1.exe
```

or through the common wrapper.

## Timing Methodology

The execution time reported for each algorithm includes only the algorithm computation.

The following are excluded:

- File reading
- Input parsing
- Memory allocation
- CSR conversion
- Output printing
- File writing

Average execution time is reported over multiple runs for GEMM.

## Test Files

### GEMM

- gemm_test_01.txt (4×4)
- gemm_test_02.txt (16×16)
- gemm_test_03.txt (32×32)
- gemm_test_04.txt (64×64)
- gemm_test_05.txt (128×128)
- gemm_test_06.txt (256×256)
- gemm_test_07.txt (512×512)

### BFS

- bfs_10.txt
- bfs_100.txt
- bfs_10000.txt
- bfs_50000.txt
- bfs_100000.txt

### DFS

- dfs_10.txt
- dfs_100.txt
- dfs_10000.txt
- dfs_50000.txt
- dfs_100000.txt

### SSSP

- sssp_10.txt
- sssp_100.txt
- sssp_10000.txt
- sssp_50000.txt
- sssp_100000.txt
