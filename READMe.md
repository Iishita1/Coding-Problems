# Coding Competitions — Practice Solutions

This repository hosts personal practice solutions for multiple coding competitions and problem sets including Xtreme 19.0 problems. Solutions are primarily in C++ (C++17) with one Python solution. Each program reads from standard input and writes to standard output, suitable for use with online judges.

## Contents

- **Languages**
  - C++ (C++17)
  - Python 3

- **Solutions (one file per problem)**
  - Airline-Travelling.cpp — 100% Acceptance
  - Application-Abuse.cpp — 100% Acceptance
  - Baker-s-Competition.cpp — 100% Acceptance
  - Beatrice-and-the-Dream-Tree.cpp — 100% Acceptance
  - Become-as-one.cpp — 100% Acceptance
  - Bitonic-Sequence.cpp — 100% Acceptance
  - Circular-Permutation.py — 100% Acceptance
  - Continued-Fractions.cpp — 100% Acceptance
  - DO-you-know-Expectation.cpp — 100% Acceptance
  - Diameter-Problem-Again.cpp — 100% Acceptance
  - Domino-Path.cpp — 100% Acceptance
  - EDPS.cpp — 100% Acceptance
  - Easy-Sum.cpp — 100% Acceptance
  - Four-Piles.cpp — 100% Acceptance
  - Hack-the-coach.cpp — 100% Acceptance
  - Ladder.cpp — 100% Acceptance
  - Magic-Wands.cpp — 100% Acceptance
  - New-Casino-Game.cpp — 100% Acceptance
  - Palindrome-Matrix.cpp — 100% Acceptance
  - Raju-s-Matrix-Runs.cpp — 100% Acceptance
  - Secure-Elliptic-Curve-Point-Addition.cpp — 100% Acceptance
  - Sequence-Decomposition.cpp — 100% Acceptance
  - Shailesh-s-Triplet.cpp — 100% Acceptance
  - Squared-Gaps.cpp — 100% Acceptance
  - Stable-Power-Network.cpp — 100% Acceptance
  - Twin-Occurence-Quest.cpp — 100% Acceptance
  - Visi-Egypt.cpp — 100% Acceptance
  - White-Knights-and-Black-Warriors.cpp — 100% Acceptance

## Build and Run

All programs are console applications. There is no shared build system; compile and run each solution independently.

- **Prerequisites**
  - C++: g++ with C++17 support (e.g., MinGW-w64 on Windows)
  - Python: Python 3.8+ (for `Circular-Permutation.py`)

- **Compile (C++)**
  - Example (Windows, MinGW):
    ```bash
    g++ -O2 -std=c++17 -pipe -static -s Easy-Sum.cpp -o Easy-Sum.exe
    ```
    If your toolchain has issues with `-static`, drop it:
    ```bash
    g++ -O2 -std=c++17 Easy-Sum.cpp -o Easy-Sum.exe
    ```

- **Run**
  - C++:
    ```bash
    .\Easy-Sum.exe < input.txt > output.txt
    ```
  - Python:
    ```bash
    python Circular-Permutation.py < input.txt > output.txt
    ```

## I/O Conventions

- Programs read input from stdin and print answers to stdout.
- No interactive prompts. Prepare input files according to the problem statements.

## Notes on Selected Solutions

- **Circular-Permutation.py**
  - Computes the minimum maximum distance any friend must move to achieve a circular ordering by height, considering both clockwise and anti-clockwise arrangements. Reduces to a 1-center on a circle over derived point sets.

- **Easy-Sum.cpp**
  - Computes a sequence of values `S_k` using prefix counts above powers of two thresholds, aggregating over all `v` where `2^v` ≤ max(A). Uses two-pointer technique per `k` for linear contributions and outputs `K` space-separated integers.

- **Four-Piles.cpp**
  - Counts tuples `(x1, x2, x3, x4)` over given ranges with `x1 ^ x2 ^ x3 ^ x4 = 0` using digit DP over bits and Inclusion–Exclusion on bounds. Supports multiple queries via a loop in `main`.

For other files, the naming follows the original problem titles; each solution is self-contained and optimized for typical contest limits (fast I/O, O2 compilation).

## Adding New Solutions

- Owner-only: Only the repository owner adds new solutions.
- Follow the same I/O style (stdin/stdout) and C++17/Python 3 standards.
- See `CONTRIBUTING.md` for structure and conventions used across problems.

## License

No explicit license is provided. Treat this repository as personal practice code unless the author specifies otherwise.

## Acknowledgments

- Currently includes problems from IEEE Xtreme 19.0. This repository is not affiliated with IEEE.

## Contributing

This is an owner-maintained repository. External contributions (pull requests) are not accepted. If you notice an issue or have a suggestion, you may open an issue. For repository conventions and structure, see `CONTRIBUTING.md`.
