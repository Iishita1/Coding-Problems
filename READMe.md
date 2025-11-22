# Coding Competitions — Practice Solutions

This repository hosts personal practice solutions for multiple coding competitions and problem sets including Xtreme 19.0 problems. Solutions are primarily in C++ (C++17) with one Python solution. Each program reads from standard input and writes to standard output, suitable for use with online judges.

## Contents

- **Languages**
  - Java (17+)
  - Python 3
  - C++ (C++17)

## Repository Structure

- **Root**
  - `CONTRIBUTING.md`
  - `READMe.md`
  - `LICENSE,md`
  - `IEEE_Xtreme_19/` — flat folder with one file per problem solution
    - `Airline-Travelling.cpp`
    - `Application-Abuse.cpp`
    - `Baker-s-Competition.cpp`
    - `Beatrice-and-the-Dream-Tree.cpp`
    - `Become-as-one.cpp`
    - `Bitonic-Sequence.cpp`
    - `Circular-Permutation.py`
    - `Continued-Fractions.cpp`
    - `DO-you-know-Expectation.cpp`
    - `Diameter-Problem-Again.cpp`
    - `Domino-Path.cpp`
    - `EDPS.cpp`
    - `Easy-Sum.cpp`
    - `Four-Piles.cpp`
    - `Hack-the-coach.cpp`
    - `Ladder.cpp`
    - `Magic-Wands.cpp`
    - `New-Casino-Game.cpp`
    - `Palindrome-Matrix.cpp`
    - `Raju-s-Matrix-Runs.cpp`
    - `Secure-Elliptic-Curve-Point-Addition.cpp`
    - `Sequence-Decomposition.cpp`
    - `Shailesh-s-Triplet.cpp`
    - `Squared-Gaps.cpp`
    - `Stable-Power-Network.cpp`
    - `Twin-Occurence-Quest.cpp`
    - `Visi-Egypt.cpp`
    - `White-Knights-and-Black-Warriors.cpp`

## Build and Run

All programs are console applications. There is no shared build system; compile and run each solution independently.

- **Prerequisites**
  - Java: JDK 17+
  - Python: Python 3.8+ (for `Circular-Permutation.py`)
  - C++: g++ with C++17 support (e.g., MinGW-w64 on Windows)

- **Compile (C++)**
  - Example (Windows, MinGW):
    ```bash
    g++ -O2 -std=c++17 -pipe -static -s Easy-Sum.cpp -o Easy-Sum.exe
    ```
    If your toolchain has issues with `-static`, drop it:
    ```bash
    g++ -O2 -std=c++17 Easy-Sum.cpp -o Easy-Sum.exe
    ```

- **Compile (Java)**
  - Example:
    ```bash
    javac Main.java
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
  - Java:
    ```bash
    java Main < input.txt > output.txt
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
- Allowed languages: Java, Python, and C++.
- Follow the same I/O style (stdin/stdout) and use Java 17+, Python 3, or C++17 standards.
- See `CONTRIBUTING.md` for structure and conventions used across problems.

## License

No explicit license is provided. Treat this repository as personal practice code unless the author specifies otherwise.

## Acknowledgments

- Currently includes problems from IEEE Xtreme 19.0. This repository is not affiliated with IEEE.

## Contributing

This is an owner-maintained repository. External contributions (pull requests) are not accepted. If you notice an issue or have a suggestion, you may open an issue. For repository conventions and structure, see `CONTRIBUTING.md`.
