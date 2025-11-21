// Domino Path (100% Acceptance)
// Time limit: 1500 ms Memory limit: 256 MB
// Almost everyone is familiar with dominoes - tiles of size 1 x 2 with two values, one on each half. In this problem, we represent each domino as a pair (x, y) where 1 < x < y < 7.
// Two dominoes can be connected if they share a common number. They are joined through that number, leaving the other two ends free.
// For example, consider dominoes (1, 3) and (2, 3). They can be connected through the number 3, resulting in a sequence with free ends 1 and 2 . Then, you could connect domino (2,5) to the end with 2, and so on.
// You are given a set of dominoes and must determine how many of its non-empty subsets hold the following condition:
// It is possible to arrange all of the dominoes in the subset to form a single continuous chain, where each adjacent pair of dominoes shares a common value.
// However, your task does not end there - you will need to answer this question for multiple test cases.
// Standard input
// The first line of input contains an integer T, the number of test cases.
// The following lines describe T test cases:
// The first line of each test case contains an integer M, the number of dominoes in the set.
// The following M lines contain two integers ; and y;, the values of each half of the domino.
// Standard output
// For each test case, print a single line, the number of subsets of the corresponding set that can form a single continuous chain.
// Constraints and notes
// .1 <T<5 × 104.
// • 1 ≤ x; <y; <7, for all valid i.
// ⚫ The sum of all M across the test cases doesn't exceed 5 x 105.
// Input
// Output
// 3
// 4
// 1 2
// 13
// 2 3
// 34
// 3
// 1 2
// 23
// 2 4
// 3
// 13
// 6
// 6
// 10 10
// 1 2
// 23
// 3 4
#include <bits/stdc++.h>
using namespace std;

const int MAX_VERTICES = 7;
const int MAX_EDGES = 21;

int edgeA[MAX_EDGES], edgeB[MAX_EDGES];
bool isEulerian[1 << MAX_EDGES];
long long subsetCount[1 << MAX_EDGES];

struct DSU {
    int parent[8];
    void init() { for (int i = 1; i <= 7; i++) parent[i] = i; }
    int find(int x) { return (parent[x] == x ? x : parent[x] = find(parent[x])); }
    void unite(int a, int b) { a = find(a); b = find(b); if (a != b) parent[a] = b; }
}; 

void precompute() {
    int index = 0;
    for (int i = 1; i <= 7; i++)
        for (int j = i + 1; j <= 7; j++)
            edgeA[index] = i, edgeB[index] = j, index++;

    int totalMasks = 1 << MAX_EDGES;
    for (int maskBits = 1; maskBits < totalMasks; maskBits++) {
        int degree[8] = {0}, vertexBits = 0;
        DSU uf; uf.init();

        for (int e = 0; e < MAX_EDGES; e++)
            if (maskBits & (1 << e)) {
                int u = edgeA[e], v = edgeB[e];
                degree[u]++; degree[v]++;
                uf.unite(u, v);
                vertexBits |= (1 << (u - 1));
                vertexBits |= (1 << (v - 1));
            }

        int oddDegreeCount = 0;
        for (int i = 1; i <= 7; i++)
            if (degree[i] & 1) oddDegreeCount++;

        if (!(oddDegreeCount == 0 || oddDegreeCount == 2)) continue;

        int root = -1;
        bool connected = true;
        for (int i = 1; i <= 7; i++)
            if (vertexBits & (1 << (i - 1))) {
                if (root == -1) root = uf.find(i);
                else if (uf.find(i) != root) connected = false;
            }

        if (connected) isEulerian[maskBits] = 1;
    }

    for (int maskBits = 0; maskBits < totalMasks; maskBits++)
        subsetCount[maskBits] = isEulerian[maskBits];

    for (int i = 0; i < MAX_EDGES; i++)
        for (int maskBits = 0; maskBits < totalMasks; maskBits++)
            if (maskBits & (1 << i))
                subsetCount[maskBits] += subsetCount[maskBits ^ (1 << i)];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    int T; 
    cin >> T;
    while (T--) {
        int M; 
        cin >> M;
        vector<pair<int, int>> edges(M);

        for (auto& [u, v] : edges) {
            cin >> u >> v;
            if (u > v) swap(u, v);
        }

        auto getIndex = [&](int a, int b) {
            int offset = 0;
            for (int i = 1; i < a; i++) offset += 7 - i;
            return offset + (b - a - 1);
        };

        int givenMask = 0;
        for (auto &[u, v] : edges)
            givenMask |= (1 << getIndex(u, v));

        cout << subsetCount[givenMask] << "\n";
    }
}