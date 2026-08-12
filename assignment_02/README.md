## Results

| Algorithm | Test File         | Vertices (V) | Edges (E) | Input Type                       | Source Vertex | Negative Cycle | Expected Output            | Actual Output              | Execution Time (ms) | Status |
| --------- | ----------------- | -----------: | --------: | -------------------------------- | :-----------: | -------| -------------------------- | -------------------------- | ------------------: | :----: |
| Bellman-Ford       | `bf_10.txt`      |           10 |        20 | Weighted Adjacency List        |       0   |    | Distances        | Correct Distances        |            |  Pass  |
| Floyd-Warshall       | `fw_10.txt`      |           10 |  Random number | Distance Matrix        |       N/A  |     | Distance Matrix        | Correct Distance Matrix       |             |  Pass  |
| Bellman-Ford      | `bf_100.txt`     |           100 |        20 | Weighted Adjacency List |       0   |    | Distances  | Correct Distances  |               |  Pass  |
| Floyd-Warshall       | `fw_100.txt`     |          100 | Random number | Distance Matrix        |       N/A  |     | Distance Matrix        | Correct Distance Matrix        |             |  Pass  |
| Bellman-Ford       | `bf_10000.txt`     |          10000 |       200 | Weighted Adjacency List        |       0 |      | Distances         | Correct Distances         |             |  Pass  |
| Floyd-Warshall      | `fw_500.txt`    |          500 |  Random number | Distance Matrix |       N/A |      | Distance Matrix | Correct Distance Matrix |               |  Pass  |
| Bellman-Ford       | `bf_50000.txt`   |        50000 |     20000 | Weighted Adjacency List        |       0 |      | Distances         | Correct Distances         |               |  Pass  |
| Floyd-Warshall       | `fw_1000.txt`   |        1000 |     Random number | Distance Matrix        |       N/A |      | Distance Matrix        | Correct Distance Matrix        |          |  Pass  |
| Bellman-Ford      | `bf_100000.txt`  |        100000 |     200000 | Weighted Adjacency List |       0 |      | Distances | Correct Distances  |              |  Pass  |
| Floyd-Warshall       | `fw_2000.txt`   |        2000 |  Random number | Distance Matrix        |       N/A   |   | Distance Matrix        | Correct Distance Matrix        |             |  Pass  |

---
