// Twin Occurence Quest (100% Acceptance)
// Time limit: 1000 ms Memory limit: 256 MB
// Hany and Sondos challenge you with a puzzle to help sharpen your skills before the contest. You are given a sorted array A. In this array, some numbers can appear more than once.
// You will receive some queries, for each query, your task is to search for a specified number X and determine both its first and its last occurrence in the array.
// Report your answer using 1-indexed positions. If X is not found, output -1 -1.
// Standard input
// The first line of input contains two space-separated integers, N and Q, the number of elements in the array and the number of queries, respectively.
// The second line contains N space-separated integers, representing A1, A2, . . ., An.
// Each of the next Q lines contains a single integer Xj, the number to search for in the array.
// Standard output
// For each query, output two space-separated integers on a new line:
// • If X is found, the 1-indexed position of the first occurrence of X in the array and the 1-indexed position of the last occurrence of X in the array.
// • If X is not found in the array, output -1 -1.
// Constraints and notes
// .1N,Q
// ·
// ·
// .
// 105.
// Ai Ai+1 for all valid i.
// |A; ≤ 109 for all i = 1,..., N.
// |X|≤ 109 for all j = 1,..., Q.
// Input
// 8 4
// 2 4 4 4 5 8 10 12
// 4
// 10
// 5
// 11
// Output
// 2 4
// 77
// 55
// -1 -1
#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

size_t lower_bound_idx(const vector<int64>& a, size_t n, int64 x) {
    size_t l = 0, r = n;
    while (l < r) {
        size_t mid = l + (r - l) / 2;
        if (a[mid] < x) l = mid + 1;
        else r = mid;
    }
    return l;
}

size_t upper_bound_idx(const vector<int64>& a, size_t n, int64 x) {
    size_t l = 0, r = n;
    while (l < r) {
        size_t mid = l + (r - l) / 2;
        if (a[mid] <= x) l = mid + 1;
        else r = mid;
    }
    return l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long Nin, Qin;
    if (!(cin >> Nin >> Qin)) {
        return 0;
    }
    if (Nin < 0) Nin = 0;
    if (Qin < 0) Qin = 0;
    size_t N = static_cast<size_t>(Nin);
    size_t Q = static_cast<size_t>(Qin);

    vector<int64> A;
    A.reserve(N);

    for (size_t i = 0; i < N; ++i) {
        int64 val;
        if (!(cin >> val)) {
            N = i;
            break;
        }
        A.push_back(val);
    }

    for (size_t qi = 0; qi < Q; ++qi) {
        int64 X;
        if (!(cin >> X)) {
            cout << "-1 -1\n";
            continue;
        }

        if (N == 0) {
            cout << "-1 -1\n";
            continue;
        }

        size_t lb = lower_bound_idx(A, N, X);
        if (lb == N || A[lb] != X) {
            cout << "-1 -1\n";
            continue;
        }
        size_t ub = upper_bound_idx(A, N, X);
        cout << (lb + 1) << " " << ub << "\n";
    }

    return 0;
}
