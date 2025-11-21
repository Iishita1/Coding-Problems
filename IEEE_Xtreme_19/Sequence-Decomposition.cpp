// Sequence Decomposition (66.67% Acceptance)
// Time limit: 1000 ms
// Memory limit: 256 MB
// An ancient ancestral saying states that the number 112012 brings good luck in any form it may appear (that is, as the number 112012, as the sequence {1, 1, 2, 0, 1, 2}, among others). Moreover, it is said that a sequence of characters consisting only of 0, 1, and 2 is considered fortunate if it can be decomposed into multiple subsequences {1, 1, 2, 0, 1, 2}.
// Miguel has some fortunate sequences, and he will only give them to you if you can find a valid decomposition for each one. It's your time to show what you're capable of!
// Note: A subsequence of a sequence S is sequence that can be derived from S by deleting zero or more elements without changing the order of the remaining elements. For example, sequence {1, 2, 3, 2, 3} contains {1, 2, 2} and {1, 3, 2} as subsequences but {2, 3, 1} is not contained as a subsequence.
// Standard input
// The first line contains an integer T, denoting the number of sequences.
// Each of the next T lines contains a sequence S; to be decomposed.
// Standard output
// For each sequence S¿, in the order of input, print lines, each containing 6 integers in increasing order, representing the indices of a subsequence {1, 1, 2, 0, 1, 2} such that all of them together decompose the sequence S;. If there are multiple valid answers, you may print any of them.
// Constraints and notes
// .1 T2 x 105. 1S6 x 105.
// •
// T
// • 1 ≤ │Si <3 × 10°.
// Input
// i=1
// S; is fortunate for all i = 1,..., T.
// Output
// 3
// 112012
// 111122001122
// 111121102110112202012212
// 1 2 3 4 5 6 1 2 5 7 9 11
// 3 4 6 8 10 12
// 1 2 5 8 13 18
// 3 4 9 12 14 21
// 6 7 15 17 20 22
// 10 11 16 19 23 24
// Explanation
// In the first case, the first line corresponds to the indices of case 1, the second and third lines to case 2, and the last four lines to case 3. Each line represents a subsequence, and all
// of them are disjoint.
#include <bits/stdc++.h>
using namespace std;

struct BuildResult {
    bool ok_full = false;                // true if full partition succeeded
    vector<array<int,6>> seqs;           // sequences (1-based indices; 0 = unset)
    vector<int> out_ids;                 // IDs to print in final order
};

// FULL partition attempt (use all chars):
// Tie-breaks: 1 -> stage1 -> start(capped) -> stage4
//             2 -> stage2 -> stage5
//             0 -> stage3
static BuildResult build_full(const string& s) {
    const int n = (int)s.size();
    // Strict feasibility by counts
    int c0=0, c1=0, c2=0;
    for (char ch : s) {
        if (ch=='0') ++c0;
        else if (ch=='1') ++c1;
        else if (ch=='2') ++c2;
        else return {};
    }
    if (n % 6 != 0) return {};
    const int k = n / 6;
    if (c0 != k || c1 != 3*k || c2 != 2*k) return {};

    vector<array<int,6>> seqs; seqs.reserve(k);
    vector<int> start_ids; start_ids.reserve(k);

    // Stage queues (FIFO via vector + head index)
    vector<int> q0; q0.reserve(k); // [1]            -> need 1
    vector<int> q1; q1.reserve(k); // [1,1]          -> need 2
    vector<int> q2; q2.reserve(k); // [1,1,2]        -> need 0
    vector<int> q3; q3.reserve(k); // [1,1,2,0]      -> need 1
    vector<int> q4; q4.reserve(k); // [1,1,2,0,1]    -> need 2
    int h0=0,h1=0,h2=0,h3=0,h4=0;

    int started = 0;

    for (int i=0, idx=1; i<n; ++i, ++idx) {
        const char ch = s[i];
        switch (ch) {
            case '1': {
                if (h0 < (int)q0.size()) {           // stage1
                    int id = q0[h0++];
                    auto &A = seqs[id];
                    if (A[1]) return {};
                    A[1] = idx;
                    q1.push_back(id);
                } else if (started < k) {            // start (capped)
                    int id = (int)seqs.size();
                    seqs.push_back({0,0,0,0,0,0});
                    auto &A = seqs[id];
                    A[0] = idx;
                    q0.push_back(id);
                    start_ids.push_back(id);
                    ++started;
                } else if (h3 < (int)q3.size()) {    // stage4
                    int id = q3[h3++];
                    auto &A = seqs[id];
                    if (A[4]) return {};
                    A[4] = idx;
                    q4.push_back(id);
                } else {
                    return {};
                }
            } break;
            case '2': {
                if (h1 < (int)q1.size()) {           // stage2
                    int id = q1[h1++];
                    auto &A = seqs[id];
                    if (A[2]) return {};
                    A[2] = idx;
                    q2.push_back(id);
                } else if (h4 < (int)q4.size()) {    // stage5
                    int id = q4[h4++];
                    auto &A = seqs[id];
                    if (A[5]) return {};
                    A[5] = idx;
                } else {
                    return {};
                }
            } break;
            case '0': {
                if (h2 < (int)q2.size()) {           // stage3
                    int id = q2[h2++];
                    auto &A = seqs[id];
                    if (A[3]) return {};
                    A[3] = idx;
                    q3.push_back(id);
                } else {
                    return {};
                }
            } break;
            default:
                return {};
        }
    }

    // Final strict checks
    if (started != k) return {};
    if (h0 != (int)q0.size() || h1 != (int)q1.size() || h2 != (int)q2.size()
        || h3 != (int)q3.size() || h4 != (int)q4.size()) return {};
    for (int id : start_ids) {
        const auto &A = seqs[id];
        if (!A[0] || !A[1] || !A[2] || !A[3] || !A[4] || !A[5]) return {};
    }

    // Canonical order: lexicographic by the 6-tuple (stricter than start-order)
    vector<int> ids = start_ids;
    sort(ids.begin(), ids.end(), [&](int a, int b){
        const auto &A = seqs[a], &B = seqs[b];
        for (int t=0; t<6; ++t) if (A[t] != B[t]) return A[t] < B[t];
        return false;
    });

    BuildResult R;
    R.ok_full = true;
    R.seqs = std::move(seqs);
    R.out_ids = std::move(ids);
    return R;
}

// MAXIMAL extraction fallback (finish as many as possible):
// Tie-breaks: 1 -> stage4 -> stage1 -> start
//             2 -> stage5 -> stage2
//             0 -> stage3
// Output only completed sequences, sorted by first index.
static BuildResult build_max(const string& s) {
    const int n = (int)s.size();

    vector<array<int,6>> seqs; seqs.reserve(n/6 + 8);
    vector<int> q0, q1, q2, q3, q4;
    q0.reserve(n/6+8); q1.reserve(n/6+8); q2.reserve(n/6+8);
    q3.reserve(n/6+8); q4.reserve(n/6+8);
    int h0=0,h1=0,h2=0,h3=0,h4=0;

    vector<int> completed; completed.reserve(n/6 + 8);

    for (int i=0, idx=1; i<n; ++i, ++idx) {
        const char ch = s[i];
        switch (ch) {
            case '0': {
                if (h2 < (int)q2.size()) {
                    int id = q2[h2++];
                    auto &A = seqs[id];
                    if (!A[3]) {
                        A[3] = idx;
                        q3.push_back(id);
                    }
                }
            } break;
            case '1': {
                bool done = false;
                if (h3 < (int)q3.size()) {           // stage4
                    int id = q3[h3++];
                    auto &A = seqs[id];
                    if (!A[4]) {
                        A[4] = idx;
                        q4.push_back(id);
                        done = true;
                    }
                }
                if (!done && h0 < (int)q0.size()) {  // stage1
                    int id = q0[h0++];
                    auto &A = seqs[id];
                    if (!A[1]) {
                        A[1] = idx;
                        q1.push_back(id);
                        done = true;
                    }
                }
                if (!done) {                         // start
                    int id = (int)seqs.size();
                    seqs.push_back({0,0,0,0,0,0});
                    auto &A = seqs[id];
                    A[0] = idx;
                    q0.push_back(id);
                }
            } break;
            case '2': {
                bool done = false;
                if (h4 < (int)q4.size()) {           // stage5
                    int id = q4[h4++];
                    auto &A = seqs[id];
                    if (!A[5]) {
                        A[5] = idx;
                        completed.push_back(id);
                        done = true;
                    }
                }
                if (!done && h1 < (int)q1.size()) {  // stage2
                    int id = q1[h1++];
                    auto &A = seqs[id];
                    if (!A[2]) {
                        A[2] = idx;
                        q2.push_back(id);
                    }
                }
            } break;
            default:
                break; // Non [0,1,2] handled in build_full; here just ignore
        }
    }

    // Deterministic order: by first index
    sort(completed.begin(), completed.end(), [&](int a, int b){
        return seqs[a][0] < seqs[b][0];
    });

    BuildResult R;
    R.ok_full = false;
    R.seqs = std::move(seqs);
    R.out_ids = std::move(completed);
    return R;
}

static inline void print_ids(const BuildResult& R) {
    for (int id : R.out_ids) {
        const auto &A = R.seqs[id];
        cout << A[0] << ' ' << A[1] << ' ' << A[2] << ' '
             << A[3] << ' ' << A[4] << ' ' << A[5] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    if (!(cin >> T)) return 0;
    while (T--) {
        string s; 
        cin >> s;

        // 1) Try  full partition (stable global policy)
        BuildResult R = build_full(s);
        if (R.ok_full) {
            print_ids(R);
            continue;
        }

        // 2) Fallback:  extraction
        R = build_max(s);
        if (!R.out_ids.empty()) {
            print_ids(R);
        } else { ; 
            cout << -1 << '\n';
        }
    };
    return 0;
}