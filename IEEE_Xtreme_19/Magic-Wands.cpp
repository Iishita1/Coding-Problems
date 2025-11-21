// Magic Wands (100% Acceptance)
// Time limit: 1000 ms
// Memory limit: 256 MB

// In the idyllic kingdom of Happy Land, there are N inhabitants, each uniquely identified by a number from 1 to N. On any given day, each inhabitant can be in a state of Happiness (H) or Sadness (S).
// The Queen, eager to ensure the well-being of her people, desires that every single inhabitant in the kingdom be happy. To achieve this, she possesses a magic wand with a peculiar power: when used, she can change the mood of exactly K consecutive people according to their id, flipping their current state (if they were happy, they become sad; if they were sad, they become happy).
// Could you help the queen fulfill her wish?
// Standard input
// The first line contains an integer T, the number of test cases.
// The following T lines contain two integers N and K, and a string S of length N consisting of characters H and 5, the number of inhabitants, the parameter K and the initial state of each inhabitant. The i-th character of S' represents the initial state of the inhabitant with ID i: H for happy, s for sad.
// Standard output
// For each test case, print a single integer - the minimum number of times the Queen must use her magic wand to make all inhabitants happy. If it is impossible to achieve this, print -1.
// Constraints and notes
// • 1≤T≤ 105.
// .1 < N, K < 105.
// ·
// • S[i] is either H or s.
// • The sum of N across all the test cases doesn't exceed 2 x 105.
// Input
// Output
// 3
// 7 3 SSHSHSS
// 4 5 HHHH
// 6 4 HSHSHS
// 3
// 0
// -1
// Explanation
// In the first test case, it's possible to use the magic wand on the range [1, 3], which will turn the sequence into
// HHSSHSS
// Then, it's possible to use the magic wand on the range [5, 7] and get
// HHSSSHH
// Finally, using the magic wand on the range [3, 5] will get everyone happy.

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>

using namespace std;

// Function to solve a single test case
void solve() {
    int N, K;
    string S;
    
    // Fast input reading for N, K, and S
    if (!(cin >> N >> K >> S)) return;

    // deque to store the starting indices of the currently active flip operations.
    // A flip starting at 'j' is active for indices i in [j, j + K - 1].
    deque<int> active_flips;
    long long flip_operations = 0; // Use long long for the count just in case, though int should suffice based on constraints

    for (int i = 0; i < N; ++i) {
        // 1. EXPIRATION: Remove flips that are no longer active at the current position 'i'.
        // A flip starting at 'j' expires at index 'j + K'.
        // If i >= j + K, the flip has ended.
        while (!active_flips.empty() && i >= active_flips.front() + K) {
            active_flips.pop_front();
        }

        // 2. DETERMINE ACTUAL STATE:
        // The parity of active_flips size tells us if the mood has been flipped an odd (1) or even (0) number of times.
        int current_flips_parity = active_flips.size() % 2;

        // The current person is SAD ('S') if the actual state is 'S'.
        // Actual State = S_original XOR current_flips_parity (where S='S' is true/1)
        bool is_sad_now;
        if (S[i] == 'S') {
            // Original state is S. It's sad if parity is even (0).
            is_sad_now = (current_flips_parity == 0);
        } else { // S[i] == 'H'
            // Original state is H. It's sad if parity is odd (1).
            is_sad_now = (current_flips_parity == 1);
        }

        // 3. GREEDY FLIP:
        if (is_sad_now) {
            // We must start a flip here to fix this sadness.
            
            // Check if a K-length flip is possible starting at 'i'.
            if (i <= N - K) {
                flip_operations++;
                active_flips.push_back(i);
                
                // This new flip fixes the state for S[i] and changes the parity for subsequent checks.
            } else {
                // Impossible: The person at 'i' is 'S' and is too close to the end (i > N - K) 
                // to be covered by any K-length flip starting at or before N-K.
                cout << -1 << "\n";
                return;
            }
        }
    }

    // 4. RESULT: If the loop finishes, all inhabitants are happy.
    cout << flip_operations << "\n";
}

int main() {
    // Optimization for fast I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0; // Read the number of test cases

    while (T--) {
        solve();
    }

    return 0;
}