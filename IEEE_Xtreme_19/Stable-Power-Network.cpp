// Stable Power Network (100% Acceptance)
// Time limit: 1000 ms Memory limit: 256 MB
// In a futuristic telecommunication network, servers are connected by bidirectional links that allow the transmission of digital messages. However, not all links are equally reliable: some introduce a risk of message corruption, and all require a certain transmission time.
// A message must be sent from server 1 to server N.
// To evaluate the quality of a route, the company defines a pair of values:
// ⚫ Maximum risk (maxR): the highest risk value among all links used in the route.
// • Total time (totalT): the sum of the transmission times of all links in the route.
// The company prioritizes safety over speed. That is, among all possible routes, it prefers the one that first minimizes max R; and, in case of a tie, the one with the smallest totalT.
// Your task is to determine the quality of the best possible transmission from server 1 to server N.
// If no such route exists, you must report it.
// Standard input
// The first line contains a single integer T, the number of test cases.
// The description of the test cases follows.
// For each test case, the first line contains two integers N and M, the number of servers and the number of links, respectively.
// Each of the next M lines contains four integers ui, vi, Wi, Ri, describing a bidirectional link:
// • Ui, Vi: the servers connected by this link.
// ⚫ W: the transmission time in milliseconds.
// ⚫R: the corruption risk of this link.
// Standard output
// For each test case, print the answer on a separate line.
// If a path exists, print two integers:
// max R totalT
// representing the quality of the best route from server 1 to server N.
// If no path exists, print -1.
// Constraints and notes
// .1 <T< 104.
// .2≤ N ≤2.105.
// .1M
// 1
// 3.105.
// ui, vi ≤ N for all i = 1,..., M.
// • ui vi for all i = 1,..., M.
// .
// .1 < W; < 109 for all i = 1,..., 1
// , M.
//  0 < Ri≤ 109 for all i = 1,..., M.
// . It is guaranteed that the sum of N over all test cases does not exceed 2. 105.
// It is guaranteed that the sum of M over all test cases does not exceed 3. 105.
// Input
// 3
// 29
// 2 1 6 3
// 2 1 25 29
// 2 1 16 21
// 1 2 29 1
// 2 1 7 95
// 2 1 16 3
// 1 2 90 56
// 2 1 86 12
// 1 2 93 83
// Output
// 1 29
// 68 45
// 79 87
// Explanation
// For the first test case, it's easy to notice that using the 4th edge we get the lowest possible risk (1) and a minimum time of 29.
// For the second test case, we can use the only edge to go from node 1 to node 8.
// For the third test case, even if there is the 3rd edge from 1 to 6 with a time of 86 and a risk of 80, it's better to use the 5th and 7th edges with a total time of 87 but a risk of 79
// 8 1
// 1 8 45 68
// 6 7
// 2 4 55 26
// 3 2 45 71
// 1 6 86 80
// 4 3 55 96
// 1 3 55 43
// 4 3 10 57
// 6 3 32 79

#include <bits/stdc++.h>

using namespace std;

// Use long long for time/distance, as it can be large
using ll = long long;
// Define a pair for (time, node) used in priority queue
using pii = pair<ll, int>;
// Define INF for distances
const ll INF = numeric_limits<ll>::max();

/**
 * @brief Finds the shortest time from node 1 to node N using Dijkstra.
 * @param N The total number of servers (nodes).
 * @param adj The adjacency list: adj[u] = vector of {v, time, risk}
 * @param max_allowed_risk Only edges with risk <= max_allowed_risk will be used.
 * @return The minimum total time to reach node N, or INF if N is unreachable.
 */
ll find_min_time(int N, const vector<vector<tuple<int, int, int>>>& adj, int max_allowed_risk) {
    vector<ll> dist(N + 1, INF);
    // Min-priority queue: stores {current_time, node}
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[1] = 0;
    pq.push({0, 1}); // Start from server 1 with time 0

    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // If this is a stale entry (we found a better path already), skip it
        if (d > dist[u]) {
            continue;
        }

        // Optimization: If we pop node N, we've found the shortest path to it
        if (u == N) {
            return d;
        }

        // Explore all neighbors
        for (const auto& edge : adj[u]) {
            int v = get<0>(edge);
            int time = get<1>(edge);
            int risk = get<2>(edge);

            // CRITICAL: Only use this edge if its risk is within the allowed limit
            if (risk <= max_allowed_risk) {
                if (dist[u] + time < dist[v]) {
                    dist[v] = dist[u] + time;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    // If we finish the loop and haven't returned, N is unreachable
    return INF;
}

// DSU (Disjoint Set Union) structure
struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        // Initialize all nodes as their own parent
        iota(parent.begin(), parent.end(), 0);
    }

    // Find the root of the set for node i (with path compression)
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    // Unite the sets containing nodes i and j
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j; // Merge i's set into j's set
            return true; // Return true if a merge happened
        }
        return false; // Already in the same set
    }
};

// Edge structure for sorting by risk
struct Edge {
    int u, v, w, r; // u, v, time, risk
    // Overload < operator to allow sorting by risk
    bool operator<(const Edge& other) const {
        return r < other.r;
    }
};


int main() {
    // Fast I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T; // Number of test cases
    while (T--) {
        int N, M;
        cin >> N >> M; // N servers, M links

        // Handle edge case: Start is the end
        if (N == 1) {
            cout << "0 0\n";
            continue;
        }

        vector<Edge> edges(M); // To be sorted by risk
        // Adjacency list for Dijkstra: adj[u] -> vector of {v, time, risk}
        vector<vector<tuple<int, int, int>>> adj(N + 1);
        
        for (int i = 0; i < M; ++i) {
            int u, v, w, r;
            cin >> u >> v >> w >> r;
            edges[i] = {u, v, w, r};
            // Build the full adjacency list for later
            adj[u].emplace_back(v, w, r);
            adj[v].emplace_back(u, w, r);
        }

        // Handle edge case: No links
        if (M == 0) { // N > 1 is implied from the check above
             cout << -1 << "\n";
             continue;
        }

        // 1. Sort all edges by risk
        sort(edges.begin(), edges.end());

        // 2. Find min_max_risk using DSU
        DSU dsu(N);
        int min_max_risk = -1;
        bool path_found = false;

        for (int i = 0; i < M; ++i) {
            dsu.unite(edges[i].u, edges[i].v);

            // Check if 1 and N are now connected
            if (dsu.find(1) == dsu.find(N)) {
                min_max_risk = edges[i].r; // This is the bottleneck risk
                path_found = true;
                break; // Found the minimal max risk
            }
        }

        if (!path_found) {
            // Iterated all edges, 1 and N are still not connected
            cout << -1 << "\n";
            continue;
        }
        
        // 3. Run Dijkstra to find min time, using the full adj list
        // but with the risk limit we just found.
        ll min_time = find_min_time(N, adj, min_max_risk);

        // If DSU found a path, Dijkstra on the same set of edges must also find one.
        cout << min_max_risk << " " << min_time << "\n";
    }

    return 0;
}

