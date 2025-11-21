// Beatrice and the Dream Tree (100% Acceptance)
// Time limit: 3000 ms Memory limit: 512 MB
// Beatrice is a university student preparing for the upcoming IEEExtreme 19.0. As part of her training, she spends countless hours thinking about trees - not the ones in nature, but the rooted ones in graph theory. Her favorite tree is a rooted tree with N nodes, rooted at node 1. She even memorized all of its edges and knows the label of every node: the i-th node has label i (1 < i < N).
// One night, Beatrice has a strange dream: she wakes up inside her favorite tree. However, the labels on all nodes are gone - she no longer knows which node she is standing on. From any node, she can only observe:
// • Which nodes it is directly connected to (its neighbors),
// • Which of those neighbors is its parent (a special edge she can always identify),
// And she can walk along edges to explore the tree.
// Moreover, Beatrice has a perfect memory: once she visits a node or a path, she will never confuse it with another.
// Beatrice wants to use her observations to deduce, without any doubt, the original label of as many nodes as possible. Unfortunately, due to the tree's structure, some nodes might be indistinguishable.
// Your task is to help Beatrice. Determine the maximum number of nodes whose original labels she can uniquely identify in her dream.
// Standard input
// The first line contains a single integer N, the number of nodes in the tree.
// Each of the next N - 1 lines contains two integers U; and V; indicating there is an edge between nodes U; and Vi.
// Standard output
// Print a single integer, the maximum number of nodes whose original labels Beatrice can uniquely identify.
// Constraints and notes
// . 2 ≤ N ≤ 106.
// .1≤ Ui, Vi≤ N for all valid i.
// Input
// Output
// Explanation
// In this example, is impossible to distinguish if you are in node 6, 7 or 8.
// 8
// 1 2
// 2 3
// 3 4
// 5
// 4 5
// 5 6
// 5 7
// 58
// 7
// 1
// 1 2
// 13
// 24
// 25
// 3 6
// 37
// In this example, is impossible to distinguish if you are in node 2 or 3, and is impossible to distinguish if you are in node 4, 5, 6 or 7.

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int n;
vector<vector<int>> adj, children;
vector<int> subtree_hash;
vector<long long> orbit_size;
map<vector<int>, int> hash_memo;
int next_hash_id = 0;

void build_tree(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            children[u].push_back(v);
            build_tree(v, u);
        }
    }
}

int compute_hash(int u) {
    vector<int> child_hashes;
    for (int v : children[u]) {
        child_hashes.push_back(compute_hash(v));
    }
    sort(child_hashes.begin(), child_hashes.end());
    
    if (!hash_memo.count(child_hashes)) {
        hash_memo[child_hashes] = next_hash_id++;
    }
    return subtree_hash[u] = hash_memo[child_hashes];
}

void compute_orbits(int u, long long parent_orbit) {
    orbit_size[u] = parent_orbit;
    
    map<int, vector<int>> groups;
    for (int v : children[u]) {
        groups[subtree_hash[v]].push_back(v);
    }
    
    for (auto& [h, nodes] : groups) {
        long long new_orbit = parent_orbit * nodes.size();
        for (int v : nodes) {
            compute_orbits(v, new_orbit);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    adj.resize(n + 1);
    children.resize(n + 1);
    subtree_hash.resize(n + 1);
    orbit_size.resize(n + 1);
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    build_tree(1, 0);
    compute_hash(1);
    compute_orbits(1, 1);
    
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (orbit_size[i] == 1) count++;
    }
    
    cout << count << "\n";
    return 0;
}
