//Palindrome Matrix (100% Acceptance)
// Time limit: 2000 ms Memory limit: 512 MB
// It's Sunday morning, and you decided to read the newspaper to solve a crossword puzzle - but today's crossword is somewhat special.
// This crossword doesn't use letters, but digits written in an N x M grid. Some cells are blocked, while the others are free.
// A word in this crossword is defined as a maximal segment of contiguous free cells in a row or column, delimited by the grid borders or blocked cells.
// Each free cell initially contains a digit. The goal is to modify these digits so that all words become palindromes, meaning they read the same from left to right and from right to left.
// Additionally, you must minimize the total sum of absolute differences between the original and modified digits.
// It is guaranteed that a valid solution always exists.
// Standard input
// The first line contains two integers N and M, the dimensions of the crossword.
// Each of the next N lines contains M characters:
// represents a blocked cell.
// • A digit d represents a free cell with initial digit d.
// Standard output
// Print the completed crossword in the same format as the input, satisfying all the conditions described.
// If there are multiple valid solutions, you must print the one that minimizes the total sum of the values in the final matrix.
// Constraints and notes
// .1 N, M≤ 1000.
// Input
// Output
// 33
// 123
// 456
// 789
// 323
// 454
// 323
// 4 3 .2.
// .1.
// -22
// .05
// .2.
// 10.
// .2.
// 11.
// 10 10
// .538...... ...4...4..
// .459157.
// 5...6..6..
// .535...... ...4...3..
// ...531135.
// 5...3..1..
// 2.11800811
// 7.16304815
// 1...6..1..
// 9...6..1..
// 5...8..3..
// 5...8..2..
// 136631.343
// 138631.351
// 2...3...7.
// 2...3...7. 7.......4.
// 5.......4.
// Explanation
// Notice that the matrix
// 727
// 2 656
// 3 727
// 4
// is also a valid answer but it's sum of values is
// 49, which is greater than matrix's
// 323
// 2
// 454
// 3 323
// 4
// which has a sum of 29.
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
int N, M;
vector<string> grid;
int par[MAXN*MAXN], rnk[MAXN*MAXN];

int find(int x) {
    if (par[x] != x) par[x] = find(par[x]);
    return par[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rnk[x] < rnk[y]) swap(x, y);
    par[y] = x;
    if (rnk[x] == rnk[y]) rnk[x]++;
}

int main() {
    cin >> N >> M;
    grid.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> grid[i];
    }
    int total = N * M;
    for (int i = 0; i < total; i++) {
        par[i] = i;
        rnk[i] = 0;
    }
    // Process rows
    for (int i = 0; i < N; i++) {
        int j = 0;
        while (j < M) {
            if (grid[i][j] == '.') {
                j++;
                continue;
            }
            int start = j;
            while (j < M && grid[i][j] != '.') j++;
            int end = j - 1;
            int len = end - start + 1;
            for (int k = 0; k < len / 2; k++) {
                int p1 = i * M + (start + k);
                int p2 = i * M + (end - k);
                unite(p1, p2);
            }
        }
    }
    // Process columns
    for (int j = 0; j < M; j++) {
        int i = 0;
        while (i < N) {
            if (grid[i][j] == '.') {
                i++;
                continue;
            }
            int start = i;
            while (i < N && grid[i][j] != '.') i++;
            int end = i - 1;
            int len = end - start + 1;
            for (int k = 0; k < len / 2; k++) {
                int p1 = (start + k) * M + j;
                int p2 = (end - k) * M + j;
                unite(p1, p2);
            }
        }
    }
    // Now, for each component, compute the best digit
    vector<vector<int>> components(total);
    for (int i = 0; i < total; i++) {
        if (grid[i / M][i % M] != '.') {
            components[find(i)].push_back(i);
        }
    }
    for (int i = 0; i < total; i++) {
        if (components[i].empty()) continue;
        vector<int> olds;
        for (int p : components[i]) {
            olds.push_back(grid[p / M][p % M] - '0');
        }
        int min_cost = INT_MAX;
        int best_d = -1;
        for (int d = 0; d <= 9; d++) {
            int cost = 0;
            for (int old : olds) {
                cost += abs(d - old);
            }
            if (cost < min_cost) {
                min_cost = cost;
                best_d = d;
            } else if (cost == min_cost) {
                best_d = min(best_d, d);
            }
        }
        for (int p : components[i]) {
            grid[p / M][p % M] = '0' + best_d;
        }
    }
    for (int i = 0; i < N; i++) {
        cout << grid[i] << endl;
    }
    return 0;
}