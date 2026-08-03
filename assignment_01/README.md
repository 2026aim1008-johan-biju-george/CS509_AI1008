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
| gemm_test_01.txt | 4×4 | Result matrix | Same as Result matrix | 0.000304 | 0.000308 | 16 | Pass |
| gemm_test_02.txt | 16×16 | Result matrix | Same as Result matrix | 0.016721 | 0.009004 | 16 | Pass |
| gemm_test_03.txt | 32×32 | Result matrix | Same as Result matrix | 0.143815 | 0.06939 | 16 | Pass |
| gemm_test_04.txt | 64×64 | Result matrix | Same as Result matrix | 0.970061 | 0.587555 | 16 | Pass |
| gemm_test_05.txt | 128×128 | Result matrix | Same as Result matrix | 7.2933 | 4.3899 | 16 | Pass |
| gemm_test_06.txt | 256×256 | Result matrix | Same as Result matrix | 58.2455 | 39.4184 | 16 | Pass |
| gemm_test_07.txt | 512×512 | Result matrix | Same as Result matrix | 334.142 | 302.575 | 16 | Pass |
