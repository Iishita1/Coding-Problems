// New Casino Game (100% Acceptance)
// Time limit: 3000 ms Memory limit: 256 MB
// The casinos in Las Vegas feel like people are not coming as much as they used to; they have a theory that it's because their games have gone stale. They have had the same games since forever! So they have come up with a new one.
// This game is played on a N x N square board, where each tile is colored white or black as in chess, such that the most common color on the board is white. Here are examples of the boards for N = 1, 2, 3, 4, 5.
// A player can come up and bet on the game; after that, N pieces will be put at random on the board, such that no two pieces are on the same row or column. The player will get 1 dollar for each piece that is on a white tile and will lose a dollar for each piece that is on a black tile. The casino has hired you to help them figure out what the expected amount of dollars they'll win is.
// Standard input
// In the first line, a number T, the number of cases you'll answer.
// On the next T lines, a number N, representing the size of the square board.
// The first line of input contains an integer N, the size of the chess board.
// Standard output
// Print T lines. On each one, an integer, the expected number of dollars the casino will have to pay to a player, taken modulo 998244353 (the answer can always be represented as an irreducible fraction a/b, where b mod 998244353 0. You have to print a · b-1
// mod 998244353).
// Constraints and notes
// .1 <T≤ 10. . 1 ≤ N ≤ 106.
// Input
// Output
// 35 2
// 1
// 598946612
// 1
// Explanation
// For the first test case, there are 120 valid bets and their total sum is 24, so the answer is 220 (mod 998244353) = 598946612 (mod 998244353).
// For the second test case, N = 2 so there are two possible scenarios:
// X.
// 2
// .X
// 3
// 2
// .X
// Xx
// X.
// L
// Where x is a chosen cell for the bet and . is an empty cell.
// It's easy to notice that The first scenario gives an income of 2 while the second one gives a loss of 2. Since the sum of both scenarios is 0 , the answer is = 0.
// For the third test case, N = 1 so there is only one possible scenario with only a white cell, so the expected amount is

#include <iostream>
#include <vector>

// The modulus: 998244353
const long long MOD = 998244353;

/**
 * @brief Computes (base^exp) % mod using modular exponentiation.
 * * @param base The base number.
 * @param exp The exponent.
 * @param mod The modulus.
 * @return long long The result of (b ase^exp) % mod.
 */
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        // If exp is odd, multiply result with base
        if (exp % 2 == 1) {
            res = (res * base) % mod;
        }
        // exp must be even now
        exp >>= 1; // exp = exp / 2
        base = (base * base) % mod; // Change base to base^2
    }
    return res;
}

/**
 * @brief Computes the modular multiplicative inverse of n modulo m.
 * * Uses Fermat's Little Theorem: n^(m-2) % m is the inverse of n mod m, 
 * since m is prime.
 * * @param n The number to find the inverse of.
 * @param m The prime modulus.
 * @return long long The inverse of n modulo m.
 */
long long modInverse(long long n, long long m) {
    return power(n, m - 2, m);
}

void solve() {
    int T;
    // Read the number of test cases T
    if (!(std::cin >> T)) return;

    while (T--) {
        long long N;
        // Read N for each test case
        if (!(std::cin >> N)) break;

        long long result;

        if (N % 2 == 0) {
            // Case 1: N is even. Expected payout is 0.
            result = 0;
        } else {
            // Case 2: N is odd. Expected payout is 1/N.
            // We compute N^(-1) mod MOD.
            
            // Note: N is guaranteed to be >= 1 and not divisible by MOD (since N <= 10^6).
            result = modInverse(N, MOD);
        }
        
        std::cout << result << "\n";
    }
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Simulate the provided input/output example
    // Input:
    // 3
    // 5
    // 2
    // 1
    
    // Expected Output:
    // 199648871 (for N=5: 5^-1 mod MOD)
    // 0 (for N=2)
    // 1 (for N=1: 1^-1 mod MOD)
    
    solve();

    return 0;
}
