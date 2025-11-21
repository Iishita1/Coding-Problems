// Secure Elliptic Curve Point Addition (100% Acceptance)
// Time limit: 1000 ms Memory limit: 256 MB
// You are implementing a cryptocurrency wallet that performs elliptic curve operations. Given an elliptic curve defined by y2 = 3 + ax + b (mod p), implement point addition.
// Standard input
// The first line of input contains an integer T, the number of test cases.
// The following I lines contain 7 integers a, b, p, x1, y1, x2, y2, the curve parameters, the prime modulus, the first point coordinates and the second point coordinates, respectively.
// Standard output
// For each test case, print a single line:
// • If result is point at infinity: POINT_AT_INFINITY.
// • Otherwise, two space-separated integers 3 and y3 which are the coordinates of the answer.
// Constraints and notes
// .1 <T< 1000.
// . 11 ≤ p ≤ 1000 (p is prime).
// .0<a<p.
// .1 <b<p.
// •
// 0x1,y1, x2, y2 <p.
// • All the points are guaranteed to be on the curve.
// Input
// 3
// Ø 7 17 2 7 2 10
// Ø 7 17 1 530
// 07 17 1 5 1 12
// Output
// POINT_AT_INFINITY
// 15 13
// POINT_AT_INFINITY
#include <iostream>
using namespace std;

long long modInverse(long long a, long long p) {
    long long m0 = p, t, q;
    long long x0 = 0, x1 = 1;
    if (p == 1) return 0;
    while (a > 1) {
        q = a / p;
        t = p;
        p = a % p;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}
//for the new testcases
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        long long a, b, p, x1, y1, x2, y2;
        cin >> a >> b >> p >> x1 >> y1 >> x2 >> y2;

        if (x1 == x2 && (y1 + y2) % p == 0) {
            cout << "POINT_AT_INFINITY\n";
            continue;
        }

        long long lambda;
        if (x1 == x2 && y1 == y2) {
            long long numerator = (3 * ((x1 * x1) % p) + a) % p;
            long long denominator = (2 * y1) % p;
            if (denominator == 0) {
                cout << "POINT_AT_INFINITY\n";
                continue;
            }
            lambda = (numerator * modInverse(denominator, p)) % p;
        } else {
            long long numerator = (y2 - y1 + p) % p;
            long long denominator = (x2 - x1 + p) % p;
            if (denominator == 0) {
                cout << "POINT_AT_INFINITY\n";
                continue;
            }
            lambda = (numerator * modInverse(denominator, p)) % p;
        }

        long long x3 = (lambda * lambda - x1 - x2) % p;
        if (x3 < 0) x3 += p;
        long long y3 = (lambda * (x1 - x3) - y1) % p;
        if (y3 < 0) y3 += p;

        cout << x3 << " " << y3 << "\n";
    }
    return 0;
}
