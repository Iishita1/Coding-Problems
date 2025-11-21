// Easy Sum (100% Acceptance)
// Time limit: 1000 ms Memory limit: 256 MB
// Victor claims he knows everything about range maximums.
// To challenge him, his teammate Miguel gives him a problem he might not be able to solve.
// You are given a sequence of positive integers A1, A2,..., Ay and an integer K.
// For each k = 1, 2,..., K, compute:
// Sk=1<<r<N log2 (max (A1, A1+1,..., A,))] × (r − 1 + 1),
// where max denotes the k-th largest element in the range (A1, At÷1, . . ., Ar),
// and is defined as 0 if the range contains fewer than k elements.
// Will Victor be able to solve this problem? Can you?
// Standard input
// The first line contains an integer N and an integer K.
// The second line contains N positive integers A¡.
// Standard output
// Print K integers, the values S1, S2,..., SK-
// Constraints and notes
// . 1 ≤ N ≤ 105. .1 < K < 20. .1 < A; ≤ 106.
// Input
// Output
// 10 10
// 10 1 9 2 8 3 7 4 6 5
// 619 522 384 272 202 134 76 36 10 0
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Function to calculate T(k, v) in O(N)
long long calculate_T(const vector<int>& P, int N, int k) {
    long long total_sum = 0;
    int r0_ptr = 1;
    for (int l = 1; l <= N; ++l) {
        int j = l - 1;
        long long target_P = P[j] + k;

        // Move r0_ptr to the first valid r >= l
        r0_ptr = max(r0_ptr, l);
        while (r0_ptr <= N && P[r0_ptr] < target_P) {
            r0_ptr++;
        }

        // If no such r exists, no subarrays starting at l (or later) will work
        if (r0_ptr > N) {
            break;
        }

        int r0 = r0_ptr;

        // All r from r0 to N are valid
        // Sum the lengths: (r0-l+1) + ... + (N-l+1)
        long long num_terms = N - r0 + 1;
        long long first_len = r0 - l + 1;
        long long last_len = N - l + 1;

        // Sum of arithmetic progression: (n/2) * (a + l)
        total_sum += (num_terms * (first_len + last_len)) / 2;
    }
    return total_sum;
}

int main() {
    // Optimize C++ IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    int max_A = 0;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        max_A = max(max_A, A[i]);
    }

    // S[k] will store the answer for k+1
    vector<long long> S(K, 0);

    int V_max = 0;
    if (max_A > 0) {
        V_max = floor(log2(max_A));
    }

    // Loop v from 1 to V_max
    for (int v = 1; v <= V_max; ++v) {
        long long threshold = 1LL << v; // 2^v

        vector<int> P(N + 1, 0);
        for (int i = 0; i < N; ++i) {
            P[i + 1] = P[i] + (A[i] >= threshold ? 1 : 0);
        }

        // For this v, calculate T(k, v) for all k
        for (int k = 1; k  <= K; ++k) {
            S[k - 1] += calculate_T(P, N, k);
        }
    }

    // Print the K answers
    for (int k = 0; k < K; ++k) {
        cout << S[k] << (k == K - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}