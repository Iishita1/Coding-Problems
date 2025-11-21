# Contributing Guide

Thank you for your interest in contributing! This repository collects general coding problems and solutions from world‑class programming competitions (e.g., ICPC, IOI, Codeforces, AtCoder, Google/Kick Start, Meta Hacker Cup, CodeChef, LeetCode Hard, Advent of Code, IEEE Xtreme, etc.). The goal is high‑quality, well‑organized problems with clear statements, references, and clean solutions.

> Note: This is an owner‑maintained repository. External contributions (pull requests) are not accepted. Public forks are welcome for personal use, but PRs from non‑owners will be closed.

## Ways You Can Contribute
- For the repository owner only:
  - **Add new problems** with statements, references, and solutions.
  - **Improve solutions** (performance, clarity, alternative approaches).
  - **Add tests** (sample I/O, edge cases, stress tests where appropriate).
  - **Refactor/maintain** structure, metadata, and documentation.

If you are not the owner: feel free to open an issue to report mistakes or suggest additions. PRs from non‑owners are not accepted.

## Repository Structure
Use this tree as a guide. Competition and year/round folders keep content organized.

```
<repo-root>/
  problems/
    <platform|contest>/<year[-round|-division]>/
      <slug>/
        README.md           # Problem statement + metadata
        solutions/
          <language>/<approach>/
            main.<ext>     # Solution entry file
            README.md       # Optional: approach explanation
        tests/
          samples/
            input1.txt
            output1.txt
            ...
          custom/           # Optional extra tests
        assets/             # Diagrams/images if needed
```

### Naming Conventions
- **Platform/Contest:** `Codeforces`, `AtCoder`, `ICPC`, `IOI`, `GoogleKickStart`, `HackerCup`, `LeetCode`, `IEEEXtreme`, etc.
- **Year/Round:** `2024`, `2024-RoundA`, `2023-Div2-Round871`, etc.
- **Slug:** short-kebab-case derived from official title, e.g., `array-division`, `infinite-table`, `tree-diameter-queries`.
- **Language folder:** `cpp`, `py`, `java`, `js`, `ts`, `go`, `rust`, `csharp`, etc.
- **Approach folder (optional):** `dp`, `greedy`, `two-pointer`, `dijkstra`, `fft`, `binary-search`, `meet-in-the-middle`.

## Required Files Per Problem
- **`README.md` (problem level):** Must contain the following sections in this order:
  - Title
  - Source/Contest with link
  - Difficulty (estimate if unofficial)
  - Tags (comma-separated)
  - Time/Memory Limits (if known)
  - Problem Statement (succinct; cite the source; do not paste copyrighted material in full if not permitted)
  - Input Format
  - Output Format
  - Sample(s): at least one sample I/O pair
  - Notes/Constraints/Edge Cases
  - Attribution and License notes (see below)

Example template:

```
# <Problem Title>

- Source: <Contest Name> (<link>)
- Difficulty: <Easy/Medium/Hard/Very Hard>
- Tags: <graphs, dp, binary-search>
- Limits: <time>, <memory>

## Statement
Short description or paraphrase. If using official text, ensure it is allowed by the contest license and include attribution.

## Input
...

## Output
...

## Samples
Input
```
<sample input>
```
Output
```
<sample output>
```

## Notes
- Key constraints and edge cases.
- Known pitfalls.

## Attribution
- Original problem: <organizer/contest> — link.
- License notes: see repository licensing section.
```

## Solutions
- Put solutions under `solutions/<language>/<approach>/`.
- Ensure the entry file is named `main.<ext>` (e.g., `main.cpp`, `main.py`).
- Include comments as needed for clarity. Prefer O(n log n) or better when feasible; document complexity.
- If the solution requires building/running instructions, include a short `README.md` in the approach folder.

### Code Style (lightweight)
- C++: C++17 or later. Use fast I/O when needed. Avoid non‑portable extensions.
- Python: 3.9+; prefer standard libs. Keep functions short and pure where possible.
- Java: 17+. Use `FastScanner`/`BufferedReader` for I/O.
- JS/TS/Go/Rust/etc.: idiomatic style, standard tooling.
- No external libraries that violate contest spirit unless the problem explicitly allows.

## Tests
- Place sample tests under `tests/samples/` as numbered pairs: `input1.txt`, `output1.txt`, etc.
- For multi‑case input formats, keep samples faithful to the original.
- Optional: add tricky edge cases under `tests/custom/` with a brief note in a `README.md` inside that folder.

## Commit Messages
- Use clear, imperative messages: `Add CF 871 Div2 A: grasshopper`, `Improve DP solution (memory -30%)`.

## Pull Request Process
Owner‑only workflow:
1. Create a branch per problem or feature.
2. Ensure the problem folder follows the structure and includes required files.
3. Ensure all sample tests pass locally for each provided solution.
4. Fill PR description with:
   - Problem source link and title
   - Summary of approach(es)
   - Complexity and any trade‑offs
   - Any licensing/attribution notes
5. Merge after self‑review or optional checks.

External PRs: Contributions from non‑owners are not accepted and will be closed.

## Licensing, Attribution, and Ethics
- Do not upload paid/proprietary statements verbatim. Prefer paraphrasing with a link, or include excerpts only if allowed by the organizer’s license.
- Always include a link to the original problem source.
- Solutions must be your own or properly attributed, and must respect the original contest rules and licenses.
- If you are a current contestant in an ongoing contest, do not submit active problems or spoilers.

## Contributor Checklist
- [ ] Folder path: `problems/<platform>/<year[-round]>/<slug>/`
- [ ] `README.md` includes: title, source link, difficulty, tags, limits, statement, I/O, samples, notes, attribution
- [ ] `solutions/<language>/<approach>/main.<ext>` with clear code and noted complexity
- [ ] `tests/samples/` with at least one input/output pair
- [ ] Builds/runs locally and passes samples
- [ ] PR description completed and references source

## Questions
Open an issue if anything is unclear or if you want feedback on a proposed structure before doing the work.

