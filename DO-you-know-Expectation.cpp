// Do you know Expectation? (100% Acceptance)
// Time limit: 1000 ms Memory limit: 256 MB
// Miguel thinks he knows a lot about probabilities, so he decided to challenge himself with the following problem to stay humble:
// You are given a sequence A1, A2,..., AN.
// A subsequence S' is chosen randomly, each element is independently picked with probability.
// Let X be the XOR of all elements in S.
// Compute the expected value of XK for a fixed K, i.e. E[X].
// Note: The XOR of an empty set is 0.
// Standard input
// The first line contains two integers N and K.
// The second line contains N integers A;, the i-th element of the sequence.
// Standard output
// Print a single line with the answer rounded up to two decimals.
// Constraints and notes
// .1 ≤ N ≤5 x 105.
// .1 < K < 6.
// .0 A; < 1024.
// Input
// 4 2
// 3.50
// 0 1 2 3
// Output
// Explanation
// For this example, the possible subsets to choose are:
// ⚫0, whose XOR is 0 and it adds 02 = 0
// to the total sum.
// ·
// {0}, whose XOR is 0 and it adds
// 02 = 0 to the total sum.
// ·
// {1}, whose XOR is 1 and it adds
// 12 = 1 to the total sum.
// .
// {0, 1}, whose XOR is 1 and it adds
// 12 = 1 to the total sum.
// .
// {2}, whose XOR is 2 and it adds
// ·
// .
// .
// .
// 22 = 4 to the total sum.
// {0,2}, whose XOR is 2 and it adds
// 22 = 4 to the total sum.
// {1, 2}, whose XOR is 3 and it adds 329 to the total sum.
// {0, 1, 2}, whose XOR is 3 and it adds
// 329 to the total sum.
// {3}, whose XOR is 3 and it adds
// 329 to the total sum.
// {0,3}, whose XOR is 3 and it adds
// 329 to the total sum.
// {1,3}, whose XOR is 2 and it adds
// 22 = 4 to the total sum.
// ·
// {0, 1, 3}, whose XOR is 2 and it adds
// 22 = 4 to the total sum.
// .
// {2, 3}, whose XOR is 1 and it adds
// .
// 12 = 1 to the total sum.
// {0, 2, 3}, whose XOR is 1 and it adds
// 12 = 1 to the total sum.
// {1, 2, 3}, whose XOR is 0 and it adds
// 02 = 0 to the total sum.
// .
// {0, 1, 2, 3}, whose XOR is 0 and it
// adds 020 to the total sum.
// So the total sum is 56 and E[X*] -
// =
// =56 =
// 3.5
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip> // For setprecision and fixed

using namespace std;

// Use __uint128_t for the sum to avoid precision loss
using u128 = __uint128_t;

/**
 * @brief Global variables
 * basis_arr: Stores the XOR basis.
 * basis_vec: Stores the non-zero basis vectors.
 * total_sum_pow_K: Accumulates the sum of v^K using exact 128-bit integers.
 * K: The power.
 */
int basis_arr[10];
vector<int> basis_vec;
u128 total_sum_pow_K = 0; // FIXED: Changed to u128
int K;

/**
 * @brief Computes base^exp as a 128-bit unsigned integer using binary exponentiation.
 * This avoids floating-point intermediate values.
 *
 * @param base The base (as int, since Ai < 1024).
 * @param exp The exponent (as int, since K <= 6).
 * @return The result as __uint128_t.
 */
u128 u128_pow(int base, int exp) {
    u128 res = 1;
    u128 b = base;
    for (int e = exp; e > 0; e /= 2) {
        if (e % 2 == 1) {
            res *= b;
        }
        b *= b;
    }
    return res;
}

/**
 * @brief Inserts a number 'x' into the XOR basis.
 * (This function was already correct)
 */
void insert_basis(int x) {
    for (int i = 9; i >= 0; --i) {
        if (!((x >> i) & 1)) {
            continue;
        }
        if (basis_arr[i] == 0) {
            basis_arr[i] = x;
            return;
        }
        x ^= basis_arr[i];
    }
}

/**
 * @brief Recursively computes the sum of v^K for all v in the span.
 *
 * @param index The current index in basis_vec.
 * @param current_xor The XOR sum accumulated so far.
 */
void compute_span_sum(int index, int current_xor) {
    // Base case: We have considered all basis vectors
    if (index == basis_vec.size()) {
        // FIXED: Use the exact integer power function
        total_sum_pow_K += u128_pow(current_xor, K);
        return;
    }
    
    // Recursive step 1: Exclude the current basis vector
    compute_span_sum(index + 1, current_xor);
    
    // Recursive step 2: Include the current basis vector
    compute_span_sum(index + 1, current_xor ^ basis_vec[index]);
}

int main() {
    // Optimize C++ I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N >> K;

    // Initialize the basis array
    for (int i = 0; i < 10; ++i) {
        basis_arr[i] = 0;
    }

    // Build the XOR basis
    for (int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        insert_basis(a);
    }

    // Collect the non-zero basis vectors
    for (int i = 0; i < 10; ++i) {
        if (basis_arr[i] > 0) {
            basis_vec.push_back(basis_arr[i]);
        }
    }

    // The dimension 'd' of the spanned vector space
    int d = basis_vec.size();

    // Compute the sum of v^K for all v in the span (V)
    compute_span_sum(0, 0);

    // E[X^K] = (1 / 2^d) * sum( v^K ) for all v in V
    
    // Calculate the number of elements in the span (2^d)
    // Since d <= 10, powl(2, d) is exact (e.g., 1024.0)
    long double num_span_elements = powl(2, d);
    
    // FIXED: Cast the exact 128-bit integer sum to long double
    // ONLY for the final division.
    long double expected_value = (long double)total_sum_pow_K / num_span_elements;

    // The rounding logic (this was already correct)
    long double final_answer = ceill(expected_value * 100.0) / 100.0;

    // Print the answer formatted to exactly two decimal places
    cout << fixed << setprecision(2) << final_answer << "\n";

    return 0;
}