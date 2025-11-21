// Hack The Coach! (100% Acceptance)

// Time limit: 2000 ms Memory limit: 512 MB
// Today your university had a very important contest, which was open for all. That's why even your coach participated on it. When you asked him about the problem D of the contest, he told you his solution but something seems strange.
// The problem D goes as follows:
// It is an interactive problem where you are lost in a country modeled as a tree with N > 2 vertices, rooted at vertex R - your hotel's location. You can query an app that, given two vertices u and v, returns their lowest common ancestor (LCA) using a function Ica(u, v). However, due to low battery, you can make at most queries. Using these limited LCA queries, you must determine the root of the tree - the location of your hotel. After doing the queries, you must print the root of the tree.
// During the contest, he wanted to be fast and trusted his instincts, so he told you he sent this solution:

//     read integer n

//     for i from 1 to n - 1:
//         read integers u, v
//         degree[u] += 1
//         degree[v] += 1
//         add v to adjacency list G[u]
//         add u to adjacency list G[v]

//     initialize empty list leaves
//     for i from 1 to n:
//         if degree[i] == 1:
//             append i to leaves

//     initialize empty list lcas
//     i = 0
//     while i + 1 < size(leaves):
//         lcas.append (leaves[i], leaves[i + 1], lca(leaves[i], leaves[i + 1]))
//         i += 2

//     if size(leaves) is odd:
//         lcas.append (leaves[0], leaves[|leaves| - 1], lca(leaves[0], leaves[|leaves| - 1]))

//     initialize empty list candidates
//     for r from 1 to n:
//         if check(r, lcas):
//             candidates.append(r)

//     assert that size(candidates) == 1
//     answer(candidates[0])

// Where check(r, Icas) is a boolean function that validates if using node r as the root is valid under the restrictions of the LCA tuples (u, v, lca (u, v)) in lcas.
// Due to weak tests he got Accepted, but you know that this idea might fail in some case, so you want to hack his solution.
// Standard input
// There is no input in this problem.
// Standard output
// Your solution should print a single file describing a tree in which the coach's solution fails.
// The first line of output must contain two integers N > 2 and 1 < R< N, the number of nodes in the tree and the root of the tree, respectively.
// The following N - 1 lines must contain two integers 1 < A; ≤ N and 1 < B; < N, the nodes connected by the corresponding edge. You must ensure that your solution prints a valid tree.
// The score obtained will be based on the value of N, the smaller, the better. To be precise, the formula for points is:
// (Your Score)2 where BestScore is the best score achieved by any team.
// BestScore

#include <iostream>

/**
 * This program outputs a test case (a tree) on which the coach's
 * LCA-based root-finding algorithm will fail.
 *
 * The failing case is a tree with N=6 and Root=1.
 * The tree has two "centers" (1 and 2), each connected to two leaves.
 *
 * Real Root (R=1):
 * 1
 * /|\
 * 3 4 2
 * / \
 * 5   6
 *
 * Leaves: {3, 4, 5, 6}
 * Coach's queries (example pairing): lca(3, 4) and lca(5, 6)
 * Real LCA results: lca_1(3, 4) = 1, lca_1(5, 6) = 2
 *
 * Fake Root (R=2):
 * 2
 * /|\
 * 5 6 1
 * / \
 * 3   4
 *
 * Fake LCA results: lca_2(3, 4) = 1, lca_2(5, 6) = 2
 *
 * Since the results for the queried pairs are identical for both R=1 and R=2,
 * the coach's algorithm will find two valid candidates (1 and 2)
 * and its assertion will fail.
 */
int main() {
    // 1. Print N and R
    // N = 6 nodes
    // R = 1 (the real root)
    std::cout << "6 1\n";

    // 2. Print the N-1 edges
    
    // Connect the two centers
    std::cout << "1 2\n";
    
    // Leaves for center 1
    std::cout << "1 3\n";
    std::cout << "1 4\n";

    // Leaves for center 2
    std::cout << "2 5\n";
    std::cout << "2 6\n";

    return 0;
}