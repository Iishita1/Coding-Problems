// Four Piles (100% Acceptance)
// Time limit: 2000 ms Memory limit: 256 MB
// You will need to process Q queries with the following problem:
// . Given A1, B1, A2, B2, A3, B3, A4, B4, compute the number of tuples (a, b, c, d) with A1 < a < B1, A2 ≤ b ≤ B2, A3 ≤ c< B3 and A4 <d< B4 such that the first player wins in a Nim game with piles (a, b, c, d).
// Can you solve this efficiently?
// Standard input
// The first line of input contains an integer Q, the number of queries.
// The following Q lines of input contain 8 integers A1, B1, A2, B2, A3, B3, A4, B4, the bounds of the queries.
// Standard output
// For each query, print a single line with the answer. Since the answer could be large, print it modulo 109 +7.
// Constraints and notes
// .1 ≤ Q≤ 1000.
// .0 A; B; ≤ 1018 for all i = 1,..., 4 in every query.
// Input
// Output
// 6
// Explanation
// For the first test case, the only valid tuple is
// . (5,5,0,5).
// For the second test case, the valid tuples are:
// (4,0,0,3).
// 3
// 5 5 5 5 0 0 5 5
// 4 5 0 1 0 2 3 4
// 1 2 4 4 2 2 1 3
// 1
// 20
// ·
// ·
// (4, 0, 1, 3).
// .
// (4, 0, 1, 4).
// .
// (4,0,2,3).
// (4,0,2,4).
// .
// (4, 1, 0, 3).
// .
// (4, 1, 0, 4).
// .
// (4, 1, 1, 3).
// ·
// (4, 1, 2, 3).
// ·
// (4, 1, 2, 4).
// ·
// (5,0,0,3).
// (5,0,0,4).
// .
// ·
// (5, 0, 1, 3).
// .
// (5,0,2,3).
// .
// (5,0,2,4).
// .
// (5, 1, 0,3).
// .
// (5, 1, 1, 3).
// .
// (5, 1, 1, 4).
// .
// (5, 1, 2, 3).
// ·
// (5, 1, 2, 4).
// For the third test case, the valid tuples are:
// . (1,4,2,1).
// .
// (1, 4, 2, 2).
// .
// (1, 4, 2, 3).
// .
// (2, 4, 2, 1).
// .
// (2, 4, 2, 2).
// .
// (2,4,2,3)

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>

using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
const int MAX_BITS = 60; // ceil(log2(10^18)) is about 60

// DP table: dp[k][tight_a][tight_b][tight_c][tight_d]
// k: current bit position (from MAX_BITS-1 down to 0)
// tight_i: 1 if number i is still equal to the prefix of its upper bound X_i
ll dp[MAX_BITS][2][2][2][2];
ll X[4]; // Current upper bounds (B_i or A_i - 1) for the DP

/**
 * Digit DP function to count tuples (a, b, c, d) such that:
 * 0 <= a <= X[0], 0 <= b <= X[1], 0 <= c <= X[2], 0 <= d <= X[3]
 * and a ^ b ^ c ^ d = 0.
 *
 * @param k The current bit position (from MAX_BITS - 1 down to -1).
 * @param tight_flags The bitmask of tight constraints (1 for a, 2 for b, 4 for c, 8 for d).
 * @param is_leading_zero Flag to handle cases where we are still filling zeros (not strictly needed here
 * since 0 is the minimum value, but helpful in general DP). Omitted for simplicity.
 * @return The number of ways to complete the numbers from bit k-1 down to 0.
 */
ll solve_dp(int k, int tight_a, int tight_b, int tight_c, int tight_d) {
    if (k == -1) {
        return 1; // Base case: all bits placed, XOR sum is 0 (enforced in transitions)
    }
    
    // Use the 4 tight flags as an index for memoization
    ll& res = dp[k][tight_a][tight_b][tight_c][tight_d];
    if (res != -1) {
        return res;
    }

    res = 0;
    
    // Max possible bit for each number based on tight constraints
    int max_bit[4] = {1, 1, 1, 1};
    if (tight_a) max_bit[0] = (X[0] >> k) & 1;
    if (tight_b) max_bit[1] = (X[1] >> k) & 1;
    if (tight_c) max_bit[2] = (X[2] >> k) & 1;
    if (tight_d) max_bit[3] = (X[3] >> k) & 1;

    // Iterate over all possible combinations of the k-th bits (bit_a, bit_b, bit_c, bit_d)
    for (int bit_a = 0; bit_a <= max_bit[0]; ++bit_a) {
        for (int bit_b = 0; bit_b <= max_bit[1]; ++bit_b) {
            for (int bit_c = 0; bit_c <= max_bit[2]; ++bit_c) {
                for (int bit_d = 0; bit_d <= max_bit[3]; ++bit_d) {
                    
                    // XOR constraint: The current bits must XOR to 0
                    if ((bit_a ^ bit_b ^ bit_c ^ bit_d) != 0) {
                        continue;
                    }
                    
                    // New tight constraints
                    int new_tight_a = tight_a && (bit_a == max_bit[0]);
                    int new_tight_b = tight_b && (bit_b == max_bit[1]);
                    int new_tight_c = tight_c && (bit_c == max_bit[2]);
                    int new_tight_d = tight_d && (bit_d == max_bit[3]);
                    
                    // Recursive call
                    res = (res + solve_dp(k - 1, new_tight_a, new_tight_b, new_tight_c, new_tight_d)) % MOD;
                }
            }
        }
    }

    return res;
}

/**
 * Calculates Count(X1, X2, X3, X4): number of tuples where 0 <= x_i <= X_i and x_1 ^ x_2 ^ x_3 ^ x_4 = 0.
 */
ll count_losing(ll X1, ll X2, ll X3, ll X4) {
    X[0] = X1; X[1] = X2; X[2] = X3; X[3] = X4;
    
    // Check for impossible counts (e.g., A_i - 1 < 0)
    if (X1 < 0 || X2 < 0 || X3 < 0 || X4 < 0) {
        return 0;
    }

    // Initialize DP table
    for (int i = 0; i < MAX_BITS; ++i) {
        for (int ta = 0; ta < 2; ++ta) {
            for (int tb = 0; tb < 2; ++tb) {
                for (int tc = 0; tc < 2; ++tc) {
                    for (int td = 0; td < 2; ++td) {
                        dp[i][ta][tb][tc][td] = -1;
                    }
                }
            }
        }
    }

    // Initial call: start from the most significant bit (59), all tight
    return solve_dp(MAX_BITS - 1, 1, 1, 1, 1);
}

/**
 * Solves the main query using the Principle of Inclusion-Exclusion (PIE).
 */
void solve() {
    ll bounds[8]; // A1, B1, A2, B2, A3, B3, A4, B4
    for (int i = 0; i < 8; ++i) {
        cin >> bounds[i];
    }
    
    ll A[4], B[4];
    for (int i = 0; i < 4; ++i) {
        A[i] = bounds[2 * i];
        B[i] = bounds[2 * i + 1];
    }

    // 1. Calculate Total Tuples (N)
    ll N = 1;
    for (int i = 0; i < 4; ++i) {
        ll range = B[i] - A[i] + 1;
        range %= MOD;
        N = (N * range) % MOD;
    }
    
    // 2. Calculate Losing Tuples (L) using PIE
    ll L = 0;
    
    // Iterate through all 2^4 = 16 subsets S of {1, 2, 3, 4} represented by a bitmask i
    for (int i = 0; i < (1 << 4); ++i) {
        ll current_X[4];
        int set_bits = 0;
        
        // Determine the upper bounds X_i for this term
        for (int j = 0; j < 4; ++j) {
            if (i & (1 << j)) {
                // j is in the subset S: X_j = A_j - 1
                current_X[j] = A[j] - 1;
                set_bits++;
            } else {
                // j is not in the subset S: X_j = B_j
                current_X[j] = B[j];
            }
        }
        
        // Calculate the count for this set of upper bounds
        ll current_count = count_losing(current_X[0], current_X[1], current_X[2], current_X[3]);

        // Apply Inclusion-Exclusion: (-1)^|S| * Count(...)
        if (set_bits % 2 == 1) {
            // Odd size subset: subtract
            L = (L - current_count + MOD) % MOD;
        } else {
            // Even size subset (or empty set): add
            L = (L + current_count) % MOD;
        }
    }
    
    // 3. Final Answer: (N - L) mod (10^9 + 7)
    ll result = (N - L + MOD) % MOD;
    
    cout << result << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Q;
    if (!(cin >> Q)) return 0;
    
    while (Q--) {
        solve();
    }
    
    return 0;
}