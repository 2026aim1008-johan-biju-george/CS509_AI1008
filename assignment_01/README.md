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

## GEMM Results

| Test File | Matrix Size | Expected Output | Actual Output | Simple Time (ms) | Blocking Time (ms) | Block Size | Status |
|-----------|-------------|----------------|---------------|-----------------:|-------------------:|-----------:|--------|
| gemm_test_01.txt | 4×4 | Correct matrix | Correct matrix | | | 16 | Pass |
| gemm_test_02.txt | 16×16 | Correct matrix | Correct matrix | | | 16 | Pass |
| gemm_test_03.txt | 32×32 | Correct matrix | Correct matrix | | | 16 | Pass |
| gemm_test_04.txt | 64×64 | Correct matrix | Correct matrix | | | 16 | Pass |
| gemm_test_05.txt | 128×128 | Correct matrix | Correct matrix | | | 16 | Pass |
| gemm_test_06.txt | 256×256 | Correct matrix | Correct matrix | | | 16 | Pass |
| gemm_test_07.txt | 512×512 | Correct matrix | Correct matrix | | | 16 | Pass |
