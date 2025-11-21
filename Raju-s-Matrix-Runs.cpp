// Raju's Matrix RUns (100% Acceptance)
// Time limit: 1000 ms Memory limit: 256 MB
// Our character Raju finds himself caught up in a matrix of order N x M, where each cell contains positive integer values. He is only allowed to move horizontally and vertically (left, right, up, and down), and no moves are allowed diagonally or outside of the matrix boundaries. Raju needs to follow a sequence of cells with increasing values and has the maximum length possible.
// The uppermost row has index 0 and the lowermost row has index N − 1, while the leftmost column has index 0 and the rightmost column has index M - 1. For example, consider the given matrix of order 4 x 4. In the given matrix, the maximum increasing sequence of values is formed by the cells (3, 1)→ (3,0) → (2, 0) → (1, 0) → (0,0) → (0, 1), so it has a length of 6.
// 8 9 6 8
// 6 2 9 9
// 4 8 9 2 2 1 8
// 4
// Can you help Raju solving this problem?
// Standard input
// The first line contains two integers N and M, representing the order of the matrix as row and column, respectively.
// The following N lines contain M integers Aij, the i-th line describes the i-th row of the matrix.
// Standard output
// The output should contain a single integer representing the maximum value of the sequence (number of cells) Raju can follow in the matrix.
// Constraints and notes
// 200.
// .1N, M • 1 Aij ≤ 231 — 1.
// Input
// -
// Output
// Explanation
// 4 4
// 8 9 6 8
// 6299
// 4892
// 2 1 8 4
// 6
// This test's answer was explained in the statement

#include <iostream>
#include <vector>
#include <algorithm> // For std::max

using namespace std;

int N, M;
vector<vector<int>> matrix; // Stores the input matrix
vector<vector<int>> dp;     // Memoization table

// Define the 4 possible moves: down, up, right, left
int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};

/**
 * @brief Performs Depth First Search (DFS) with memoization to find
 * the longest increasing path starting from cell (r, c).
 * @param r The current row.
 * @param c The current column.
 * @return The length of the longest increasing path starting from (r, c).
 */
int dfs(int r, int c) {
    // If this state has already been computed, return the stored value.
    if (dp[r][c] != 0) {
        return dp[r][c];
    }

    // Initialize the longest path starting from (r, c) as 1 (the cell itself).
    int max_len = 1;

    // Explore all 4 adjacent cells
    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i]; // New row
        int nc = c + dc[i]; // New column

        // Check if the new cell is within the matrix boundaries
        if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
            // Check if the value is strictly increasing
            if (matrix[nr][nc] > matrix[r][c]) {
                // If it is, the path length is 1 + the longest path from the new cell
                max_len = max(max_len, 1 + dfs(nr, nc));
            }
        }
    }

    // Store the computed result in the dp table and return it.
    return dp[r][c] = max_len;
}

int main() {
    // Optimize C++ standard input/output
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Read matrix dimensions
    cin >> N >> M;

    // Resize the matrix and dp table
    matrix.assign(N, vector<int>(M));
    dp.assign(N, vector<int>(M, 0)); // Initialize dp table with 0 (not computed)

    // Read the matrix values
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> matrix[i][j];
        }
    }

    int global_max_len = 0;
    // We need to find the longest path, which can start from *any* cell.
    // So, we call dfs for every cell (if it hasn't been computed yet)
    // and find the maximum result.
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            global_max_len = max(global_max_len, dfs(i, j));
        }
    }

    // Print the final answer
    cout << global_max_len << "\n";

    return 0;
}