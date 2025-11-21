// AIrline Travelling (100% Acceptance)
// Time limit: 1500 ms Memory limit: 256 MB
// Sebastian has been saving a lot of miles on his card for traveling. However, his favorite airline, 'Star Airlines', is going out of business and taking their miles with them! Sebastian wants to use his miles while he can, so he decides to take one last trip, and he wants to use all his miles, even if he has to go through any one city more than once.
// 'Star Airlines' is a pretty weird airline. They are a local airline that operates only in Star Country and has N cities, with the capital being city 0. 'Star Airlines' has flights from the capital city to every other city and from every city to the capital, but not between cities.
// Sebastian knows the cost in miles of flying from the capital to any city, and he knows it's the same price the other way around. To plan his last trip, he needs to see his options, so he will ask you if it is possible to travel from city A to city B while using all his miles. Help him by answering his questions!
// Standard input
// The first line of input contains 2 integers N and k, the number of cities in the country and the number of miles Sebastian has.
// The second line of input contains N - 1 integers C1,... CN-1, where C; is the cost in miles to go from the capital to city i.
// The third line of input contains an integer Q, the number of queries you'll have to answer.
// In the next Q lines, 2 integers A; and By, the queries Sebastian will ask you.
// Standard output
// Print Q lines, Yes if it is possible to go from city Aj to Bj, or No otherwise.
// Constraints and notes
// • 1 < N, Q≤ 106. .1 < k < 10000.
// . 1 ≤ C;
// .0
// Input
// 1000 for all i = 1,..., N − 1. Aj, Bj < N for all j = 1,..., Q.
// 3 4
// 1 2
// 2
// 0 0
// 0 1
// Output
// Yes
// No
// Explanation
// The given star country looks like this:
// 2
// 1
// 2
// 1
// https://csacademy.com/ieeextreme19/task/airline-traveling/statement/
// For the first query, it's easy to see that Sebastian can use the path 0→2→ 0 to consume the 4 miles.
// For the second query, it's impossible to find a path starting in 0 and ending in 1 such that the miles consumed sum up to 4
#include <iostream>
#include <vector>
#include <set>

using namespace std;

// This DP array will be shared by all queries
vector<bool> dp_half;

int main() {
    // Optimize C++ I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, k;
    cin >> N >> k;

    // costs[i] will store the cost for city i
    vector<int> costs(N, 0); 
    set<int> unique_costs;
    for (int i = 1; i < N; ++i) {
        cin >> costs[i];
        unique_costs.insert(costs[i]);
    }

    // --- 1. Pre-compute the DP table ---
    int max_half_sum = k / 2;
    dp_half.assign(max_half_sum + 1, false);
    dp_half[0] = true; // Base case: 0 miles is always possible

    // Unbounded knapsack DP
    for (int c : unique_costs) {
        for (int i = c; i <= max_half_sum; ++i) {
            if (dp_half[i - c]) {
                dp_half[i] = true;
            }
        }
    }

    // --- 2. Answer Queries ---
    int Q;
    cin >> Q;
    while (Q--) {
        int A, B;
        cin >> A >> B;

        bool possible = false;
        int target_round_trip_sum = -1; // Default to an impossible value

        if (A == 0 && B == 0) {
            // Case 1: Base path cost = 0
            target_round_trip_sum = k;
        } else if (A == 0 && B != 0) {
            // Case 2: Base path 0 -> B
            target_round_trip_sum = k - costs[B];
        } else if (A != 0 && B == 0) {
            // Case 3: Base path A -> 0
            target_round_trip_sum = k - costs[A];
        } else {
            // Case 4: Base path A -> 0 -> B
            target_round_trip_sum = k - costs[A] - costs[B];
        }

        // Check if this target sum is possible
        if (target_round_trip_sum >= 0 && 
            target_round_trip_sum % 2 == 0) {
            
            int half_sum = target_round_trip_sum / 2;
            
            // We only computed DP up to max_half_sum (k/2).
            // The largest possible half_sum we need to check is k/2.
            if (half_sum <= max_half_sum) {
                possible = dp_half[half_sum];
            }
        }

        if (possible) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
 
    return 0;
}