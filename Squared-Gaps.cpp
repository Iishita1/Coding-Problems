// Squared Gaps (100% Acceptance)
// Time limit: 3000 ms Memory limit: 512 MB
// You are given two DNA sequences consisting of the uppercase english characters A, G, T and C. In the classical sequence alignment problem, the alignment cost is calculated based on three factors: match (when the same characters from both sequences are aligned), mismatch (when different characters are aligned), and gap (when a character is aligned with a space).
// In this variation of the problem, the gap cost is modified. Specifically, when multiple consecutive spaces are aligned together in one sequence, the cost for this segment of m spaces is calculated as m2. (gap cost) rather than just m⚫ (gap cost). These space segments must be maximal, meaning there must not be any additional spaces to the left or right of the segments in the corresponding sequence after the alignment.
// Given two sequences and the costs for a match, a mismatch, and a gap, your task is to determine the maximum possible alignment cost between these two sequences using the modified gap cost rule.
// Standard input
// The first line of input contains an integer n, the length of the first sequence.
// The second line of input contains a string a of length n, the first sequence.
// The third line of input contains an integer m, the length of the second sequence.
// The fourth line of input contains a string b of length m, the second sequence.
// The fifth line of input contains three integers match, mismatch and gap, the cost of a match, mismatch and a gap, respectively.
// Standard output
// Print a single line, the optimal alignment cost of the two given sequences.
// Constraints and notes
// . 1 ≤ n, m≤ 106.
// •-103 < gap < mismatch < 0 < match < 103.
// • It is guaranteed that nm doesn't exceed 106.
// Input
// 7
// GATAAGC
// 8
// CGCCTAAC
// 15 -3 -20
// 1
// C
// U 00
// 8
// TCGCGTGG
// 1 -3 -19
// 5
// GCGTC
// 10
// GGAGTAATCA
// 3 -2 -3
// Output
// 13
// -474
// Explanation
// The optimal alignment is:
// GATAAGC
// 2 CGCCTA AC
// 3
// And has only one space segment of length 1,
// 3 matches and 4 mismatches. Its value is 12. (-20)+3.15 + 4 · (−3) = 13.
// The optimal alignment is:
// -10
// 2 TCGCGTGG
// 3
// And has two space segments of lengths 3 and 4 and 1 match. Its value is 32. (-19)+42 · (19) + 1 · 1 = −474.
// The optimal alignment is:
// 2
// 3
// G-C-G-TC- GGAGTAATCA
// And has five space segments of length 1, 2 mismatches and 3 matches. Its value is 5. 12. (-3)+2(-2) + 3. 3 = −10.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

// Use long long for all costs and DP values
using ll = long long;
// Use __int128_t for CHT slope calculations to prevent overflow
using i128 = __int128_t;

// A very small number (negative infinity)
const ll INF = 1e18;

// Point structure for CHT
struct Point {
    ll x, y; // x = i' (or j'), y = g(i') - G*(i')^2
};

// Function to calculate slope for CHT check
// Use 128-bit int to avoid overflow during cross-product
bool is_bad(Point p1, Point p2, Point p3) {
    // We check if p2 is below or on the line segment p1-p3
    // (p2.y - p1.y) * (p3.x - p2.x) <= (p3.y - p2.y) * (p2.x - p1.x)
    i128 lhs = (i128)(p2.y - p1.y) * (p3.x - p2.x);
    i128 rhs = (i128)(p3.y - p2.y) * (p2.x - p1.x);
    return lhs <= rhs;
}

// Add a point to the upper hull (deque)
void add_to_hull(deque<Point>& hull, Point p_new) {
    while (hull.size() >= 2) {
        Point p2 = hull.back();
        Point p1 = hull[hull.size() - 2];
        if (is_bad(p1, p2, p_new)) {
            hull.pop_back();
        } else {
            break;
        }
    }
    hull.push_back(p_new);
}

// Query the hull for the max(y + m*x)
// Slopes m = 2Gi (or 2Gj) are monotonically increasing
Point query_hull(deque<Point>& hull, ll m_q) {
    while (hull.size() >= 2) {
        Point p1 = hull[0];
        Point p2 = hull[1];
        // Check if p2 is better than p1 for slope m_q
        // p1.y + m_q * p1.x <= p2.y + m_q * p2.x
        if (p1.y + m_q * p1.x <= p2.y + m_q * p2.x) {
            hull.pop_front();
        } else {
            break;
        }
    }
    return hull.front();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    string a, b;
    ll match, mismatch, gap;

    cin >> n >> a >> m >> b >> match >> mismatch >> gap;

    ll G = -gap; // G is positive

    // DP tables, initialized to -INF
    vector<vector<ll>> dp_match(n + 1, vector<ll>(m + 1, -INF));
    vector<vector<ll>> dp_gapA(n + 1, vector<ll>(m + 1, -INF)); // Gap in b
    vector<vector<ll>> dp_gapB(n + 1, vector<ll>(m + 1, -INF)); // Gap in a

    // CHT structures: one per column for dp_gapA
    vector<deque<Point>> hulls_A(m + 1);

    for (int i = 0; i <= n; ++i) {
        // CHT structure: one for the current row i for dp_gapB
        deque<Point> hull_B;

        for (int j = 0; j <= m; ++j) {
            ll val_m = -INF, val_a = -INF, val_b = -INF;

            // Handle base cases explicitly
            if (i == 0 && j == 0) {
                val_m = 0;
            } else if (i == 0 && j > 0) {
                // Align b[1..j] with j spaces
                val_b = 1LL * gap * j * j;
            } else if (j == 0 && i > 0) {
                // Align a[1..i] with i spaces
                val_a = 1LL * gap * i * i;
            }

            // 1. Calculate DP_match[i][j]
            if (i > 0 && j > 0) {
                ll score = (a[i - 1] == b[j - 1]) ? match : mismatch;
                ll prev = max({dp_match[i - 1][j - 1], dp_gapA[i - 1][j - 1], dp_gapB[i - 1][j - 1]});
                if (prev != -INF) {
                    val_m = score + prev;
                }
            }

            // 2. Calculate DP_gapA[i][j] using CHT on column j
            if (i > 0 && !hulls_A[j].empty()) {
                ll m_q = 2LL * G * i;
                Point best = query_hull(hulls_A[j], m_q);
                // val = max(y + m*x) - G*i^2
                val_a = best.y + m_q * best.x - 1LL * G * i * i;
            }

            // 3. Calculate DP_gapB[i][j] using CHT on row i
            if (j > 0 && !hull_B.empty()) {
                ll m_q = 2LL * G * j;
                Point best = query_hull(hull_B, m_q);
                // val = max(y + m*x) - G*j^2
                val_b = best.y + m_q * best.x - 1LL * G * j * j;
            }

            // Store the computed values
            // (dp_match[0][0] will be 0, others will be -INF or base case)
            dp_match[i][j] = max(dp_match[i][j], val_m);
            dp_gapA[i][j] = max(dp_gapA[i][j], val_a);
            dp_gapB[i][j] = max(dp_gapB[i][j], val_b);

            // 4. Update CHT structures
            
            // Update hulls_A[j] (for column j) with point from row i
            // g(i) = max(dp_match[i][j], dp_gapB[i][j])
            ll g_A = max(dp_match[i][j], dp_gapB[i][j]);
            if (g_A != -INF) {
                // Point is (i, g(i) - G*i^2)
                add_to_hull(hulls_A[j], {i, g_A - 1LL * G * i * i});
            }

            // Update hull_B (for row i) with point from column j
            // g(j) = max(dp_match[i][j], dp_gapA[i][j])
            ll g_B = max(dp_match[i][j], dp_gapA[i][j]);
            if (g_B != -INF) {
                // Point is (j, g(j) - G*j^2)
                add_to_hull(hull_B, {j, g_B - 1LL * G * j * j});
            }
        }
    } 

    // The final answer is the max of the three states at (n, m)
    ll ans = max({dp_match[n][m], dp_gapA[n][m], dp_gapB[n][m]});
    cout << ans << "\n";

    return 0;
}