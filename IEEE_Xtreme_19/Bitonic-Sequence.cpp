//Bitonic Sequence (100% Acceptance)
// Time limit: 2000 ms Memory limit: 128 MB

// We define a positive bitonic sequence of sum N as a sequence of positive integers S1, S2,..., Sk such that (Summation)S=N,and there exists an i=1
// index j satisfying:
//     Si (is smaller than or equal to) Si+1 for all 1 < i < j, and
//     Si (is greater than or equal to) Si+1 for all j < i <k.

// Find the number of distinct positive bitonic sequences with total sum N, for all 1 ≤ N ≤ M, modulo 109 + 7.
// Two bitonic sequences S1 and S2 are considered different if they have different lengths, or if there exists an index j such that S1.j (is not equal to) S2.j
// Standard input
// The first line of input contains a single integer M.
// Standard output
// Print the number of distinct positive bitonic sequences for each N (1 ≤ N ≤ M), modulo 109 + 7.
// Constraints and notes
// .1 <M<3 × 105.
// Input
// 5
// Output
// Explanation
// 1 2 4 8 15
// For N = 5, these are the valid bitonic sequences:
// . {1,1,1,1,1}. {2,1,1,1}. {1,2,1,1}.
// ·
// .
// {1, 1, 2, 1}.
// .
// {1,1,1,2}.
// .
// {3,1,1}.
// .
// {1,3,1}.
// ·
// • {1,1,3}.
// •{2,2,1}.
// . {1,2,2}.
// • {4,1}.
// ·
// • {1,4}.
// .
// .
// • {2,3}.
// .
// • {3,2}.
// .
// {5}.
// Notice that {2, 1, 2} is not a valid bitonic sequence.
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    vector<int> p(M + 1, 0);
    p[0] = 1;

    // Block 1: Calculate p[n] (partition numbers)
    // This is O(M * sqrt(M)) - This is efficient and correct.
    for (int n = 1; n <= M; ++n) {
        long long sum = 0;
        for (int k = 1; ; ++k) {
            int g1 = k * (3 * k - 1) / 2;
            int g2 = k * (3 * k + 1) / 2;
            if (g1 > n) break;
            int sign = (k % 2 == 1 ? 1 : -1);
            sum = (sum + (long long)sign * p[n - g1]) % MOD;
            if (g2 <= n) sum = (sum + (long long)sign * p[n - g2]) % MOD;
        }
        p[n] = (sum % MOD + MOD) % MOD;
    }

    // Block 2: Calculate r[n]
    // This is the OPTIMIZED O(M * sqrt(M)) block.
    // It replaces the original O(M^2) block.
    // We use the recurrence: r[n] = p[n] + sum( (-1)^(k+1) * (r[n-g1] + r[n-g2]) )
    vector<int> r(M + 1, 0);
    r[0] = 1; // Base case: r[0] = p[0]*p[0] = 1
    for (int n = 1; n <= M; ++n) {
        long long sum = 0;
        for (int k = 1; ; ++k) {
            int g1 = k * (3 * k - 1) / 2;
            int g2 = k * (3 * k + 1) / 2;
            if (g1 > n) break;
            int sign = (k % 2 == 1 ? 1 : -1); // This is (-1)^(k+1)
            sum = (sum + (long long)sign * r[n - g1]) % MOD;
            if (g2 <= n) sum = (sum + (long long)sign * r[n - g2]) % MOD;
        }
        // r[n] = p[n] + sum
        r[n] = (p[n] + sum) % MOD;
        r[n] = (r[n] + MOD) % MOD; // Handle potential negative sum
    }

    // Block 3: Compute result res[n] using r[n-t]
    // This is O(M * sqrt(M)) - This is efficient and correct.
    vector<int> res(M + 1, 0);
    for (int n = 1; n <= M; ++n) {
        long long total = 0;
        for (int k = 1; ; ++k) {
            int t = k * (k + 1) / 2; // Triangular numbers
            if (t > n) break;
            // Add/subtract r[n-t] based on k
            total = (total + (k % 2 == 1 ? r[n - t] : MOD - r[n - t])) % MOD;
        }
        res[n] = total;
    }

    // Output
    for (int i = 1; i <= M; i++)
        cout << res[i] << (i < M ? ' ' : '\n');

    return 0;
}