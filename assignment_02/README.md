## Results

| Algorithm | Test File         | Vertices (V) | Edges (E) | Input Type                       | Source Vertex | Negative Cycle | Expected Output            | Actual Output              | Execution Time (ms) | Status |
| --------- | ----------------- | -----------: | --------: | -------------------------------- | :-----------: | -------| -------------------------- | -------------------------- | ------------------: | :----: |
| Bellman-Ford       | `bf_10.txt`      |           10 |        20 | Weighted Adjacency List        |       0   |  No  | Distances        | Correct Distances        |   0.0124         |  Pass  |
| Floyd-Warshall       | `fw_10.txt`      |           10 |  N/A | Distance Matrix        |       N/A  |     | Distance Matrix        | Correct Distance Matrix       |            |  Pass  |
| Bellman-Ford      | `bf_100.txt`     |           100 |        200 | Weighted Adjacency List |       0   |  No  | Distances  | Correct Distances  |   0.5525            |  Pass  |
| Floyd-Warshall       | `fw_100.txt`     |          100 | N/A | Distance Matrix        |       N/A  |     | Distance Matrix        | Correct Distance Matrix        |             |  Pass  |
| Bellman-Ford       | `bf_10000.txt`     |          10000 |       20000 | Weighted Adjacency List        |       0 |   Yes   | N/A         | N/A         |  5998.78           |  Fail  |
| Floyd-Warshall      | `fw_500.txt`    |          500 |  N/A | Distance Matrix |       N/A |      | Distance Matrix | Correct Distance Matrix |               |  Pass  |
| Bellman-Ford       | `bf_50000.txt`   |        50000 |     100000 | Weighted Adjacency List        |       0 |  Yes  | N/A         | N/A        |   290953            |  Fail  |
| Floyd-Warshall       | `fw_1000.txt`   |        1000 |  N/A | Distance Matrix        |       N/A |      | Distance Matrix        | Correct Distance Matrix        |          |  Pass  |
| Bellman-Ford      | `bf_100000.txt`  |        100000 |     200000 | Weighted Adjacency List |       0 |   Yes   | N/A | N/A  |  941781            |  Pass  |
| Floyd-Warshall       | `fw_2000.txt`   |        2000 |  N/A | Distance Matrix        |       N/A   |   | Distance Matrix        | Correct Distance Matrix        |             |  Pass  |

---

## Bellman-Ford and Floyd-Warshall Cross-Check

For the required graph sizes of 10 and 100 vertices, the same generated
graph was used for both Bellman-Ford and Floyd-Warshall.

Bellman-Ford was executed from every vertex as the source. The resulting
shortest-path distances were compared with the corresponding row of the
Floyd-Warshall distance matrix.

- V = 10: Cross-check passed.
- V = 100: Cross-check passed.

Therefore, the Bellman-Ford and Floyd-Warshall implementations produced
matching shortest-path distances for all source vertices on both test cases.
