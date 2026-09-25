# Pathfinder

Pathfinder is a command-line shortest-path solver written in C. It reads a weighted, undirected graph of islands and bridges, calculates the minimum distance between every pair of islands, and prints the routes that achieve those distances.

The project uses the Floyd-Warshall algorithm for distance calculation and a backtracking pass to reconstruct every shortest route, including alternative routes with the same total distance.

## Features

- Finds shortest paths between every pair of islands.
- Supports multiple shortest routes with equal total distance.
- Validates bridge descriptions and island names.
- Detects duplicate bridges.
- Rejects invalid or oversized bridge distances.
- Uses strict Clang warnings during compilation.

## Quick Start

### Requirements

- macOS or another Unix-like operating system
- Clang
- Make

### Build

```sh
make all
```

This creates the `pathfinder` executable and builds the local `Libmx` static library.

To remove build artifacts:

```sh
make clean
```

To clean and rebuild everything:

```sh
make reinstall
```

### Run

Pass exactly one input file to the executable:

```sh
./pathfinder file
```

Or use your own graph:

```sh
./pathfinder input.txt
```

## Input Format

The first line contains the number of islands. Each following line describes one undirected bridge:

```text
number_of_islands
island-island,distance
```

Example:

```text
4
A-B,1
C-D,1
C-B,1
```

Input rules:

- Island names contain alphabetic characters only.
- Bridge distances are positive integers.
- A bridge cannot connect an island to itself.
- Duplicate bridges are rejected, including reversed duplicates such as `A-B` and `B-A`.
- The total bridge length must fit within the supported integer range.

## Example Output

For the sample input above, Pathfinder prints results such as:

```text
========================================
Path: A -> D
Route: A -> B -> C -> D
Distance: 1 + 1 + 1 = 3
========================================
```

When multiple routes have the same shortest distance, each route is printed separately.

## How It Works

1. The parser reads island and bridge definitions from the input file.
2. The graph is stored as a distance matrix.
3. Floyd-Warshall checks whether travelling through an intermediate island is shorter:

```text
distance[i][j] = min(distance[i][j],
distance[i][k] + distance[k][j])
```

4. A backtracking pass follows the calculated distances to reconstruct the shortest routes.
5. The routes and their individual bridge distances are printed to standard output.

## Project Structure

```text
.
|-- inc/              Pathfinder public headers
|-- Libmx/            Static utility library
|-- src/              Parser, graph, algorithm, and output code
|-- file              Sample graph input
|-- Makefile          Build commands
`-- README.md         Project documentation
```

## Implementation Notes

- Time complexity: `O(V^3)` for Floyd-Warshall, where `V` is the number of islands.
- Additional route reconstruction work depends on the number of shortest routes.
- Compiler flags include `-Wall`, `-Wextra`, `-Werror`, and `-Wpedantic`.

## License

No license has been specified for this repository yet.
