// White Knights and Black Warriors (100% Acceptance)
// Time limit: 1000 ms Memory limit: 256 MB
// The IEEExtreme programming competition is in full swing, and teams from all over the world are solving tough problems. Two rival teams, the "White Knights" and the "Black Warriors", have their own nodes on a vast network of computers that form a tree structure. Each node is either controlled by the White Knights (white nodes) or the Black Warriors (black nodes).
// The competition administrators, including you, want to track how close each team gets to the White Knights' nodes during their journey across the network. To do this, you've been given several tasks where you must find the shortest distance to a white node as teams travel between two specific nodes, U and V, in the network.
// As the competition heats up, your job is to help the teams by determining how close they are to passing by a white node as they navigate between different points in the tree. This insight could be crucial for their strategies!
// Standard input
// The first line contains two integers N and Q, where N is the number of nodes (computers) in the network and Q is the number of queries. The second line contains N integers, where the i-th integer is 1 if the node is white (controlled by the White Knights) or O if it is black (controlled by the Black Warriors).
// The next N - 1 lines each contain two integers a; and b2, representing a connection between the two nodes a¿ and b¿.
// The following Q lines each contain two integers U; and Vi, representing a query where you need to determine the shortest distance to a white node on the path between U; and Vi.
// Standard output
// For each query, output the minimum distance to a white node on the path between U; and V. It's guaranteed that at least a white node exists.
// Constraints and notes
// . 1 ≤ N ≤ 106.
// .1 <Q≤ 106.
// .1≤ui, vi ≤ N for all valid i. .1≤ Ui, Vi≤ N for all valid i.
// Input
// Output
// Explanation
// The given graph is the following:
// 8 1
// 0 1 10 000е
// 1 2
// 13
// 1 4
// 0
// 25
// 4 6
// 4 7
// 38
// 5 8
// 5
// 2
// 8
// 1
// 3
// 6
// 4
// Since the path from 5 to 8 contains the nodes 5 →2→ 1→ 3 → 8 and both 2 and 3 are white nodes, the answer is 0.
// 12 M
// 3
// 2
// 1100000
// 456787
// The given graph is the following:
// 5
// 2
// 8
// 3
// 1
// 6
// 4
// Since the path from 6 to 7 contains the nodes 6 →4→ 7, the answer must be 2 since the distance between node 4 and any of the white nodes is 2. Nodes 6 and 7 have a distance of 3.
// 1
// 0 0 0 0 0
// 2
// 3
// 4
// Since the path from 6 to 7 contains the nodes 6 →4→7, the answer must be 2 since the distance between node 4 and any of the white nodes is 2. Nodes 6 and 7 have a distance of 3.
// The given graph is the following:
// 4
// 5
// 6
// 6
// 5
// 2
// 3
// 6
// Since the path from 5 to 6 contains the nodes 5→ 6, the answer must be 4 since the distance between node 5 and the only white node is 4. Node 6 has a distance of 5

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const int LOGN = 20;
const int INF = 1e9;

int N, Q;
vector<int> adj[MAXN];
int color[MAXN];
int dist_to_white[MAXN];
int depth[MAXN];
int parent[MAXN];
int up[MAXN][LOGN];
int path_min[MAXN][LOGN];

void run_bfs() {
    queue<int> q;
    for (int i = 1; i <= N; ++i) {
        dist_to_white[i] = INF;
        if (color[i] == 1) {
            dist_to_white[i] = 0;
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist_to_white[v] > dist_to_white[u] + 1) {
                dist_to_white[v] = dist_to_white[u] + 1;
                q.push(v);
            }
        }
    }
}

void dfs(int u, int p) {
    parent[u] = p;
    for (int v : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

void build_lifting() {
    for (int i = 1; i <= N; ++i) {
        up[i][0] = parent[i];
        path_min[i][0] = min(dist_to_white[i], dist_to_white[parent[i]]);
    }
    
    for (int j = 1; j < LOGN; ++j) {
        for (int i = 1; i <= N; ++i) {
            int mid = up[i][j-1];
            if (mid == 0) {
                up[i][j] = 0;
                path_min[i][j] = path_min[i][j-1];
            } else {
                up[i][j] = up[mid][j-1];
                path_min[i][j] = min(path_min[i][j-1], path_min[mid][j-1]);
            }
        }
    }
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    
    int diff = depth[u] - depth[v];
    for (int j = 0; j < LOGN; ++j) {
        if (diff & (1 << j)) {
            u = up[u][j];
        }
    }
    
    if (u == v) return u;
    
    for (int j = LOGN - 1; j >= 0; --j) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return parent[u];
}

int query_path(int u, int v) {
    int lca = get_lca(u, v);
    int result = INF;
    
    // Query from u to lca
    int diff = depth[u] - depth[lca];
    int curr = u;
    for (int j = 0; j < LOGN; ++j) {
        if (diff & (1 << j)) {
            result = min(result, path_min[curr][j]);
            curr = up[curr][j];
        }
    }
    
    // Query from v to lca  
    diff = depth[v] - depth[lca];
    curr = v;
    for (int j = 0; j < LOGN; ++j) {
        if (diff & (1 << j)) {
            result = min(result, path_min[curr][j]);
            curr = up[curr][j];
        }
    }
    
    // Include lca itself
    result = min(result, dist_to_white[lca]);
    
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;
    for (int i = 1; i <= N; ++i) {
        cin >> color[i];
    }
    
    for (int i = 0; i < N - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    run_bfs();
    depth[1] = 0;
    dfs(1, 0);
    build_lifting();
    
    while (Q--) {
        int u, v;
        cin >> u >> v;
        cout << query_path(u, v) << '\n';
    }
    
    return 0;
}