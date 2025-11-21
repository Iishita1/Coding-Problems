// Visit Egypt (100% Acceptance)
// Time limit: 2000 ms Memory limit: 256 MB
// Mikel and Andrew plan to visit Egypt and want to exchange their Euros into Egyptian Pounds. 1 Egyptian Pound is divided into 100 Egyptian Piastres and Egypt's currency denominations include 25 and 50 Piastre coins, and 1, 5, 10, 20, 50, 100, and 200 Pound notes.
// Upon exchanging their money, Mikel and Andrew decide to engage in a game where they predict the number of possible ways to convert their Euros into Egyptian currency.
// However, since they know that the number of ways could be large, they will consider that value modulo 109 +7 in their guesses. For this, consider that order does matter, so using a coin of 50 Piastre and then a note of 100 Pounds is considered a different way than using first a note of 100 Pounds and then a coin of 50 Piastre.
// Can you determine who wins the game?
// Note 1: One Euro equals 53 Egyptian Pounds.
// Note 2: One Egyptian Pound equals 100 Egyptian Piastres.
// Standard input
// The first line of input contains an integer T, the number of test cases.
// The following T lines of input contain three integers N, M and A, the given Euro amount, and the predictions from both Mikel and Andrew, respectively.
// Standard output
// For each test case, determine the winner of the game.
// • If one prediction is closer to the actual number of combinations, print the name of the winner (Mikel or Andrew).
// • If both predictions are equally distant from the actual number, print NONE.
// • If both predictions match the actual number, print TIE.
// Constraints and notes
// .1 <T< 105.
// . 1 ≤ N ≤ 105.
// .0
// M, A < 109 +7.
// Input
// 5
// 10 10 25
// 1 443443317 3000000
// 40 338770238 338770238 60 338770238 318903897
// 100 572914301 572914315
// Output
// Andrew
// Mikel
// TIE
// Andrew
// NONE
// Explanation
// For the first test case, the correct answer is 96479252, so Andrew wins because it's distance is smaller than Mikel's.
// For the second test case, the correct answer is 443443317, so Mikel wins because it's distance is smaller than Andrew's.
// For the third test case, the correct answer is 338770238, so both Andrew and Mikel got
// it right and it's a tie.
// For the fourth test case, the correct answer is 318903897, so Andrew wins because it's distance is smaller than Mikel's.
// For the fifth test case, the correct answer is 572914308, so none of them wins since both have a distance of 7 with respect to the correct answer.
#include <iostream>
#include <vector>
#include <cmath> // For abs()

using namespace std;

// Define the modulo
const int MOD = 1000000007;

// Define the maximum N and the maximum target k'
const int N_MAX = 100000;
const int K_PRIME_MAX = N_MAX * 212;

// Denominations in "25 Piastre" units
const vector<int> denominations = {1, 2, 4, 20, 40, 80, 200, 400, 800};

// dp array to store the number of ways
// We use long long to prevent overflow during intermediate addition before modulo
vector<long long> dp(K_PRIME_MAX + 1);

/**
 * @brief Precomputes the number of ways for all target amounts up to K_PRIME_MAX.
 */
void precompute() {
    // Base case: 1 way to make an amount of 0 (use no currency)
    dp[0] = 1;

    // Fill the dp array
    for (int k = 1; k <= K_PRIME_MAX; ++k) {
        dp[k] = 0; // Initialize ways for current amount k
        
        // Sum up the ways from previous states
        for (int d : denominations) {
            if (k - d >= 0) {
                // Add the number of ways to make (k - d)
                dp[k] = (dp[k] + dp[k - d]) % MOD;
            }
        }
    }
}

int main() {
    // Optimize C++ standard streams for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Run the precomputation once
    precompute();

    int T;
    cin >> T; // Read the number of test cases

    while (T--) {
        int n;
        long long m, a; // Mikel's and Andrew's predictions
        cin >> n >> m >> a;

        // Calculate the target amount in "25 Piastre" units
        int target_k = n * 212;

        // Get the correct answer from our precomputed array
        long long correct_answer = dp[target_k];

        // Calculate the absolute differences
        // Use long long for differences to be safe
        long long diff_m = abs(correct_answer - m);
        long long diff_a = abs(correct_answer - a);

        // Determine the winner
        if (diff_m < diff_a) {
            cout << "Mikel\n";
        } else if (diff_a < diff_m) {
            cout << "Andrew\n";
        } else {
            // Differences are equal
            if (diff_m == 0) {
                // Both are correct
                cout << "TIE\n";
            } else {
                // Both are equally wrong
                cout << "NONE\n";
            }
        }
    }

    return 0;
}