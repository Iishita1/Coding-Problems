//Shailesh's Triplet (100% Acceptance)
// Time limit: 2000 ms Memory limit: 256 MB
// Shailesh has an upcoming tournament. For that he has to choose 3 integers. So he comes up with an interesting idea. Given an integer N, he will select the positive integers A, B, C such that no two of them are equal i.e., (A B, AC, BC) which satisfy the following conditions: . A+B+C 2. N.
// • A B C = N (where represents Bitwise XOR operator).
// As Shailesh is busy with Turing Hut club works, he asks your help in identifying the integers A, B, C. So, find any 3 integers that satisfy the above conditions.
// Standard input
// Each test contains multiple test cases. The first line contains the number of test cases T. The description of the test cases follows.
// First and only line contains a single integer N.
// Standard output
// For each testcase, print three space separated integers A, B and C if they satisfy the given conditions, otherwise print -1 on a new line.
// In case of multiple triplets which satisfy the conditions, print any triplet.
// Constraints and notes
// .1 <T< 105. • 1 ≤ N <263
// Input
// 3
// 20
// 7
// 52
// Output
// 22 8 10
// -1
// 54 24 26
// Explanation
// In the first testcase, 22+8+ 10 = 40 and 2281020. There are multiple triplets possible, {18, 8, 14} is also a valid triplet for N = 20.
// In the second testcase, there exists no triplet that satisfies the given conditions.
// In the third testcase, {24, 18, 62} is one of the valid triplets possible.
#include <bits/stdc++.h>
using namespace std;
using u128 = __uint128_t;
using u64 = unsigned long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        u64 N;
        cin >> N;
        if (N & 1ULL) {
            cout << -1 << '\n';
            continue;
        }

        bool printed = false;
        if (N >= 4) { 
            u64 A0 = N / 2;
            u64 B0 = A0 - 1;
            u64 C0 = N + 1;
            u128 sum = (u128)A0 + (u128)B0 + (u128)C0;
            u128 twoN = (u128)N * 2U;
            if (sum == twoN) {
                u64 xr = (A0 ^ B0 ^ C0);
                if (xr == N && A0 != B0 && A0 != C0 && B0 != C0 && B0 > 0) {
                    cout << A0 << ' ' << B0 << ' ' << C0 << '\n';
                    printed = true;
                }
            }
        }

        if (printed) continue;

        bool found = false;
        for (int i = 0; i <= 60 && !found; ++i) {
            u64 bit = (1ULL << i);
            u64 C = N ^ bit;
            if (C == 0) continue;            
            u128 twoN = (u128)N * 2U;
            if ((u128)C > twoN) continue; 
            u128 S128 = twoN - (u128)C;
            if (S128 == 0) continue;
            u64 X = N ^ C;
            if ((u128)X > S128) continue;
            u128 diff = S128 - (u128)X;
            if ((diff & 1U) != 0) continue;
            u128 Y128 = diff / 2U; 
            if (Y128 == 0) continue;
            if (Y128 > (u128)ULLONG_MAX) continue; 
            u64 Y = (u64)Y128;
            if ((X & Y) != 0) continue;

            u128 A128 = (u128)X + (u128)Y;
            if (A128 == 0 || A128 > (u128)ULLONG_MAX) continue;
            u64 A = (u64)A128;
            u64 B = Y;
            if (A == B || A == C || B == C) continue;
            if (B == 0 || C == 0 || A == 0) continue;

            u128 sum = (u128)A + (u128)B + (u128)C;
            u128 twoNchk = (u128)N * 2U;
            if (sum != twoNchk) continue;
            u64 xr = (A ^ B ^ C);
            if (xr != N) continue;

            cout << A << ' ' << B << ' ' << C << '\n';
            found = true;
            break;
        }

        if (!found) {
            cout << -1 << '\n';
        }
    }
    return 0;
}
