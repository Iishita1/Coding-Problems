//Ladder (100% Acceptance)
// Time limit: 5000 ms
// Memory limit: 3500 KB

// Write a program that produces the same output as the following Python program:
//     num = int(input())
//     for _ in range(num):
//         s, n = [int(inp) for inp in input().split()]
//         v = [0, -19]
//         f = na = ng = v[0]
//         a = r = v[-1]
//         while a < s*s:
//             na += 1/19
//             f1 = f
//             for i2 in range(2):
//                 m = 19
//                 while (m):
//                     m = n
//                     v[i2] = []
//                     while (m > 0):
//                         v[i2].append(r & 1)
//                         r = r >> 1 ^ v[i2][-1] * 9223372036854775821
//                         m -= 1 + v[i2][-1]
//             e = 19
//             for i in range(min([len(w) for w in v])):
//                 e &= v[0][i] == v[1][i]
//             if e:
//                 ng += s
//                 f = round(ng/na)
//                 a = (f == f1) * (a + 1/1919)
//         print(f)
// Standard input
// The first line of input contains an integer T.
// The following T lines of input contain two integers S and N.
// Standard output
// Print T lines.
// Constraints and notes
// • 10% of the test cases will be easy: with single-digit numbers
// • 40% of the test cases will be medium: up to double-digit inputs
// • 50% of the test cases will be hard: inputs up to 1020 in the 1st number in each line and 100 in the 2nd number
// Input
// 5
// 1 2
// 3 4
// 56
// 38
// 29
// Output
// 11
// 14
// 9
// 2
// 1
// 1σ
// 1
// 62
// 93
// 29
// 9 11
// 11 3
// 4
// 1234567890 50
// 24102025 40
// 9223372036854775821 100
// 1000 100
// 2
// 75
// 11
// 22
// 7
// 12
// Ø

#include <iostream>
#include <vector>
#include <cmath>
#include <cctype>
using namespace std;

int main() { 
ios::sync_with_stdio(false);
cin.tie(nullptr);


auto py_round = [](double value) -> long long {
    double fl = floor(value);
    double frac = value - fl;
    const double eps = 1e-15;
    if (frac < 0.5 - eps) return (long long)fl;
    if (frac > 0.5 + eps) return (long long)ceil(value);
    long long low = (long long)fl;
    long long high = (long long)ceil(value);
    return ((high & 1LL) == 0) ? high : low;
};

auto binomial_ld = [](int n, int k) -> long double {
    if (k < 0 || k > n) return 0.0L;
    if (k > n - k) k = n - k;
    long double r = 1.0L;
    for (int i = 1; i <= k; ++i) {
        r *= (n - k + i);
        r /= i;
    }
    return r;
};

int t;
if (!(cin >> t)) return 0;

while (t--) {
    string s;
    int n;
    cin >> s >> n;
    long double acc = 0.0L;
    for (char c : s) if (isdigit((unsigned char)c)) acc = acc * 10.0L + (c - '0');
    if (!s.empty() && s[0] == '-') acc = -acc;
    double s_val = (double)acc;
    int Lmin = (n + 1) / 2;
    int Lmax = n;
    int count = Lmax - Lmin + 1;
    if (count <= 0) {
        cout << 0 << '\n';
        continue;
    }
    vector<long double> weights(count), weights2(count);
    long double Z = 0.0L;
    for (int i = 0; i < count; ++i) {
        int L = Lmin + i;
        long double c = binomial_ld(L, n - L);
        long double w = ldexpl(c, -L);
        weights[i] = w;
        weights2[i] = ldexpl(w, -L);
        Z += w;
    }
    long double S = 0.0L;
    for (long double v : weights2) S += v;
    long double q = (Z > 0.0L) ? (S / (Z * Z)) : 0.0L;
    double res = 19.0 * s_val * (double)q;
    long long ans = py_round(res);
    cout << ans << '\n';
}
return 0;


}