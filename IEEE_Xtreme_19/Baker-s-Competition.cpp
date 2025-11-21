// Baker's Competition (100% Acceptance)
// Time limit: 1500 ms Memory limit: 256 MB
// Mr. Baker is well-known for his baking skills, especially for making sliced cakes. He is hosting a competition. However, this competition is not a direct cake-eating competition as everyone thought. To win the competition, you have to solve the puzzle given below:
// Mr Baker will provide N cakes (unsliced) of unique sizes from 1 to N and place them accordingly to their size. He will then choose a segment of the cakes and ask each competitor to solve the following problem:
// • A competitor will choose two cakes from the segment.
// • The competitor will have to slice both cakes with the same slice size p > 1.
// • The slice size must be the same for all the slices.
// ⚫p should be a prime number.
// • The number of slices of each cake should be a prime number.
// The competitor has to count the number of such pairs of cakes in the segment. Pair (i, j) is equivalent to pair (j, i).
// Mr Baker may ask to solve this puzzle for multiple segments. The winner of the competition will be the one who answers all the puzzles correctly, and they will receive all the unsliced cakes!
// As a cake-lover, can you answer the questions Mr Baker is going to ask?
// Standard input
// The first line contains an integer T denoting the number of puzzles Mr Baker is going to ask.
// The following I lines will contain two integers L and R denoting the first cake size and the last cake size from Mr Baker's segment of cakes, respectively.
// Standard output
// For each puzzle, print the number of pairs that fulfill Mr Baker's conditions.
// Constraints and notes
// .1 <T< 105.
// • N = 106.
// .1<L<R≤N.
// Input
// 2
// 1 100
// 1 1000
// 2
// 1 10
// 1 20
// Output
// 224
// 9563
// 4
// 10
// Explanation
// One of the valid pairs in the first test case is
// (4, 6), since we can choose p = 2 and get 2 and 3 slices from each cake.
// For the first test case, all the valid pairs are:
// ·
// (4, 6), choosing p = 2 and getting 2
// and 3 slices.
// ⚫ (4,10), choosing p = 2 and getting 2
// .
// .
// and 5 slices.
// • (6,9), choosing p = 3 and getting 2
// and 3 slices.
// . (6,10), choosing p = 2 and getting 3
// and 5 slices.

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000;
vector<int> primes;
vector<bool> is_prime(MAXN + 1, true);
vector<pair<int, int>> items;

void sieve() {
    is_prime[0] = is_prime[1] = false;
    for (long long i = 2; i <= MAXN; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (long long j = i * i; j <= MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

void precompute() {
    sieve();
    for (size_t i = 0; i < primes.size(); i++) {
        int p = primes[i];
        for (size_t j = i; j < primes.size(); j++) {
            int q = primes[j];
            if (1LL * p * q > MAXN) break;
            int m = p * q;
            items.push_back({m, p});
            if (p != q) items.push_back({m, q});
        }
    }
    sort(items.begin(), items.end());
}

struct Query {
    int L, R, idx;
};

int BLOCK;  // global block size for Mo's ordering

bool cmp(const Query &a, const Query &b) {
    int ba = a.L / BLOCK, bb = b.L / BLOCK;
    if (ba != bb) return ba < bb;
    return (ba & 1) ? (a.R > b.R) : (a.R < b.R);  // slight optimization
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();
    int T;
    cin >> T;
    vector<Query> queries;
    vector<long long> answers(T);

    for (int t = 0; t < T; t++) {
        int L, R;
        cin >> L >> R;

        auto it1 = lower_bound(items.begin(), items.end(), make_pair(L, -1));
        auto it2 = upper_bound(items.begin(), items.end(), make_pair(R, INT_MAX));

        int left = it1 - items.begin();
        int right = (it2 - items.begin()) - 1;

        if (left > right) {
            answers[t] = 0;
            continue;
        }
        queries.push_back({left, right, t});
    }

    BLOCK = sqrt(items.size()) + 1;
    sort(queries.begin(), queries.end(), cmp);

    vector<long long> freq(MAXN + 5, 0);
    long long current = 0;
    int cl = 0, cr = -1;

    for (auto &q : queries) {
        int l = q.L, r = q.R;

        while (cr < r) {
            cr++;
            int p = items[cr].second;
            current += freq[p];
            freq[p]++;
        }
        while (cl > l) {
            cl--;
            int p = items[cl].second;
            current += freq[p];
            freq[p]++;
        }
        while (cr > r) {
            int p = items[cr].second;
            freq[p]--;
            current -= freq[p];
            cr--;
        }
        while (cl < l) {
            int p = items[cl].second;
            freq[p]--;
            current -= freq[p];
            cl++;
        }
        answers[q.idx] = current;
    }

    for (int t = 0; t < T; t++) {
        cout << answers[t] << '\n';
    }

    return 0;
}
