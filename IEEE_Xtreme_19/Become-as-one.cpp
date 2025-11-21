// Become as One (100% Acceptance)
// Time limit: 1000 ms Memory limit: 256 MB
// Given an array A of N integers, you will have to answer Q queries (Li, R;). For each query, you must answer whether the subarray A[L¿, Ri] holds the following property:
// • An operation is defined as taking two occurrences of a value X, removing those occurrences and adding X + 1 to the elements. Determine if A[Li, Ri] can finish with only 1 element after a certain number of operations.
// Standard input
// The first line of input contains two integers N and Q, the length of the array and the number of queries, respectively.
// The second line of input contains N integers A;, the i-th integer is the i-th element of the array.
// The following Q lines of input contain two integers Li and Ri, the 2-th line contains the bounds of the subarray for the i-th query.
// Standard output
// For each query, print Yes if the corresponding subarray holds the property or No otherwise.
// Constraints and notes
// .1 < N, Q≤ 106.
// .0 A; 30 for all i = 1,..., N.
// • 1 ≤ L; ≤ R; ≤ N for all i = 1,..., Q.
// Input
// Output
// 74
// 0 3 1 3 4 1 4
// 6 6
// 5 5
// 4 6
// 1 2
// Yes Yes
// No
// No

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

/**
 * @brief Checks if a 64-bit integer is a power of 2.
 * * A positive integer S is a power of 2 if and only if it has exactly one bit set.
 * In binary, this means S > 0 and S & (S - 1) == 0.
 * * @param S The number to check.
 * @return true if S is a power of 2, false otherwise.
 */
bool is_power_of_two(long long S) {
    // S must be positive
    if (S <= 0) {
        return false;
    }
    // The bitwise trick: a power of 2 has only one '1' bit, 
    // and S - 1 flips all bits after and including the least significant '1' bit.
    // If there is only one '1' bit, S & (S - 1) will be 0.
    return (S & (S - 1)) == 0;
}

void solve() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, Q;
    if (!(std::cin >> N >> Q)) return;

    // The core insight: The operation preserves the sum of 2^A_i.
    // Sum for A[Li, Ri] = sum_{j=Li}^{Ri} 2^{A_j} must be a power of 2.
    // Since N is up to 10^6 and max(A_i) is 30, the max sum is ~10^6 * 2^30,
    // which fits within a 64-bit integer (long long).

    // Prefix sum array P. P[i] will store the sum of 2^A_j for j=1 to i.
    // P is 1-indexed to match the problem statement (size N+1).
    std::vector<long long> P(N + 1, 0);

    for (int i = 1; i <= N; ++i) {
        int A_i;
        if (!(std::cin >> A_i)) return;
        
        // Calculate 2^A_i. Use a left shift for speed: 1LL << A_i
        // The 1LL ensures the operation is done using long long.
        long long power_of_two = 1LL << A_i;
        
        // Calculate the prefix sum
        P[i] = P[i - 1] + power_of_two;
    }

    // Process Q queries
    for (int k = 0; k < Q; ++k) {
        int L, R;
        if (!(std::cin >> L >> R)) return;

        // The sum for the subarray A[L, R] is P[R] - P[L - 1].
        // This is the total sum of 2^A_i over the subarray.
        long long subarray_sum = P[R] - P[L - 1];

        // Check if the sum is a power of 2
        if (is_power_of_two(subarray_sum)) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }
}

int main() {
    solve();
    return 0;
}