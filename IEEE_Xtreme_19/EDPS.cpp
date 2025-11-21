// EDPS (100% Acceptance)
// Time limit: 2000 ms Memory limit: 512 MB
// According to an ancient tale, the answer to all of humankind's questions is a spell protected by a logical structure known as a Well- Parenthesized Sequence (WPS).
// A WPS is a string consisting only of the characters (and ), satisfying the following properties:
// . The empty string is a WPS.
// • The concatenation of two WPSS is also a WPS.
// • A WPS enclosed in a pair of parentheses is also a WPS.
// A pair of parentheses is defined as a matching pair (,) that directly encloses a WPS.
// It is known that every WPS of length 2N contains exactly N such pairs.
// The original spell has been lost, but researchers managed to recover one crucial piece of information: the multiset of distances between each matching pair of parentheses, that is, the number of symbols that appear between each (and its corresponding ).
// Now the researchers need your help to reconstruct any valid WPS of length 2N that has exactly N pairs of parentheses with the given distances. This is called an Exactly Distanced Parentheses Sequence (EDPS).
// If no such sequence exists, you must report it.
// Standard input
// The first line contains an integer N, the number of parenthesis pairs in the spell.
// The second line contains N integers A1, A2,..., AN - the distances between the parentheses of each pair.
// Standard output
// • If there exists a WPS that satisfies all the given distances, print Yes on the first line, and on the second line print a string of length 2N consisting only of the characters (and ), representing a valid sequence. If there are multiple valid sequences, you may output any of them.
// • If no WPS satisfies the given conditions, print a single line with No.
// Constraints and notes
// . 1 ≤ N ≤ 20.
// ⚫ 0 ≤ A; < 2N for all i = 1,..., N.
// Input
// Output
// 1
// 0
// Yes
// ()
// 2
// O
// 00
// Yes
// 00
// 2 2
// 20
// 1 2
// 5
// ☹
// 00026
// Yes
// (())
// No
// Yes
// ((0)0)0
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>

using namespace std;

// Global variables for the problem state
int N;
vector<int> distances;
vector<char> res; // result parenthesis array (size 2*N)

/**
 * @brief Recursive backtracking function to place parenthesis pairs.
 * * @param index The index of the distance in the sorted 'distances' array to place next.
 * @return true if a valid placement is found for the current and remaining distances, false otherwise.
 */
bool backtrack(int index) {
    // Base case: if all N distances have been successfully placed
    if (index == N) {
        // Fill remaining empty slots with the smallest pairs "()"
        // This is necessary because the problem setup implies a balanced
        // sequence must be formed, and the given N distances only
        // determine N pairs of a specific minimum size.
        // The remaining slots must form additional valid, minimum-size pairs.
        
        vector<int> empty_slots;
        for (int i = 0; i < 2 * N; ++i) {
            if (res[i] == '\0') {
                empty_slots.push_back(i);
            }
        }

        // The number of remaining empty slots must be even, and they must form pairs.
        if (empty_slots.size() % 2 != 0) {
            // This case should ideally not be reached if the structure is correct,
            // as the placed pairs always take an even number of slots (d+2).
            return false;
        }

        // Fill empty slots with "()" pairs: The i-th empty slot gets '('
        // and the (i+1)-th empty slot gets ')' for i = 0, 2, 4, ...
        for (size_t i = 0; i < empty_slots.size(); i += 2) {
            if (i + 1 < empty_slots.size()) {
                res[empty_slots[i]] = '(';
                res[empty_slots[i+1]] = ')';
            } else {
                // Should not happen if size is even
                return false; 
            }
        }
        
        return true;
    }

    int d = distances[index];
    int length = d + 2; // span of the pair including parentheses

    // Try all possible starting positions for this pair
    for (int start = 0; start <= 2 * N - length; ++start) {
        int end = start + length - 1;

        // Check if all positions for the pair (start to end) are free
        bool positions_free = true;
        for (int i = start; i <= end; ++i) {
            if (res[i] != '\0') {
                positions_free = false;
                break;
            }
        }

        if (!positions_free) {
            continue;
        }

        // Try placing the pair
        res[start] = '(';
        res[end] = ')';

        // Recursively place the rest
        if (backtrack(index + 1)) {
            return true;
        }

        // Backtrack: remove the placed pair
        res[start] = '\0';
        res[end] = '\0';
    }

    return false;
}

void solve() {
    // 1. Read N
    if (!(cin >> N)) return;

    // 2. Read distances
    distances.resize(N);
    for (int i = 0; i < N; ++i) {
        if (!(cin >> distances[i])) return;
    }

    // 3. Sort distances in descending order (same as Python)
    sort(distances.rbegin(), distances.rend());

    // 4. Initialize result array (using null character '\0' for empty)
    res.assign(2 * N, '\0');

    // 5. Start backtracking
    if (backtrack(0)) {
        cout << "Yes" << endl;
        // Convert vector<char> to string and print
        string result_str(res.begin(), res.end());
        cout << result_str << endl;
    } else {
        cout << "No" << endl;
    }
}

// The main function structure
int main() {
    // Fast I/O is often a good practice in competitive programming in C++
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}