//  Continued Fractions (100% Acceptance)
// Time limit: 4000 ms
// Memory limit: 256 MB
// Miguel is studying the behavior of some continued fractions.
// A continued fraction [A1; A2, ..., Ak] represents the value
// Time limit: 4000 ms Memory limit: 256 MB
// 1
// A1 +
// 1
// A2 +
// 1 Ak
// Miguel starts with a sequence S1, S2,..., SN, where each S; represents a continued fraction value.
// He then performs M global operations on this sequence:
// -S;+X for 1 <i<N.
// • Operation 1 X: add X to all elements, that is, S; ← • Operation 2: invert all elements, that is, S; ← 1/Si.
// Miguel guarantees that all values will be invertible when this operation is applied.
// After each operation, Miguel must print the sum of all current values:
// Si.
// For simplicity, you must output the result modulo 998244353.
// Standard input
// The first line contains two integers N and M.
// The second line contains N integers S; representing the initial values of the sequence.
// Each of the next M lines describes one operation:
// • 1X: add X to all elements.
// • 2: invert all elements.
// Standard output
// N
// Print M lines. The j-th line should contain the sum S; after applying the j-th operation, reduced modulo 998244353.
// Constraints and notes
// . 1 ≤ N ≤ 105.
// •1<M<6×104
// .1 S; < Si
// .0 X
// 998244353 for all i = 1,..., N.
// 998244353.
// Input
// 55
// 1 2 3 4 5
// 11
// 2
// 1 1
// 2
// SNHN 2
// Output
// 20
// 349385525
// 349385530
// 292342993 349385530
// Explanation
// Initially, our sequence is:
// S = {1, 2, 3, 4, 5}
// After the first query, the sequence turns into:
// S = {2, 3, 4, 5, 6}
// whose sum is 20.
// After the second query, the sequence turns into:
// =
// 1 1 1 1
// whose sum is 229.149736653
// (mod 998244353) = 349385525
// (mod 998244353)
// After the third query, the sequence turns into:
// 3 4 5 6
// s = {1,1,1, 8, 7}
// =
// whose sum is 129 129.149736653 (mod 998244353) = 349385530 (mod 998244353)
// After the fourth query, the sequence turns into:
// S
// 3 4 5 6
// s = {1,1,1,8,9)
// whose sum is 547547.591816295
// (mod 998244353) = 292342993
// (mod 998244353)
// After the fifth query, the sequence turns into:
// 4 5 6
// S = {1,1,1, 9, 7}
// whose sum is 129 129.149736653
// =
// (mod 998244353) = 349385530
// (mod 998244353)
#include <bits/stdc++.h>
using namespace std;

// Modulo 998244353, NTT-friendly
const int MOD = 998244353;
const int G = 3;

int addmod(int a,int b){ a+=b; if(a>=MOD) a-=MOD; return a; }
int submod(int a,int b){ a-=b; if(a<0) a+=MOD; return a; }
long long modpow(long long a,long long e){ long long r=1%MOD; while(e){ if(e&1) r=r*a%MOD; a=a*a%MOD; e>>=1;} return r; }
int inv(int x){ return (int)modpow(x, MOD-2); }

void ntt(vector<int>& a, bool invert){
    int n = a.size();
    static vector<int> rev;
    if ((int)rev.size() != n){
        int k = __builtin_ctz(n);
        rev.assign(n,0);
        for(int i=0;i<n;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
    }
    for(int i=0;i<n;i++) if(i<rev[i]) swap(a[i], a[rev[i]]);
    for(int len=1; len<n; len<<=1){
        long long wlen = modpow(G, (MOD-1)/(len<<1));
        if(invert) wlen = inv(wlen);
        for(int i=0;i<n;i+=len<<1){
            long long w=1;
            for(int j=0;j<len;j++){
                int u=a[i+j];
                int v=(int)((long long)a[i+j+len]*w%MOD);
                a[i+j]=u+v<MOD?u+v:u+v-MOD;
                a[i+j+len]=u-v>=0?u-v:u-v+MOD;
                w = w * wlen % MOD;
            }
        }
    }  
    if(invert){
        int inv_n = inv(n);
        for(int &x: a) x = (long long)x*inv_n % MOD;
    }
}

vector<int> multiply(const vector<int>& a, const vector<int>& b){
    if(a.empty()||b.empty()) return {};
    int n = 1; while(n < (int)a.size() + (int)b.size() - 1) n <<= 1;
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n); fb.resize(n);
    ntt(fa, false); ntt(fb, false);
    for(int i=0;i<n;i++) fa[i] = (long long)fa[i] * fb[i] % MOD;
    ntt(fa, true);
    fa.resize(a.size() + b.size() - 1);
    return fa;
}

vector<int> poly_add(const vector<int>& a, const vector<int>& b){
    vector<int> r(max(a.size(), b.size()));
    for(size_t i=0;i<r.size();++i){
        int av = i<a.size()?a[i]:0;
        int bv = i<b.size()?b[i]:0;
        r[i] = addmod(av,bv);
    }
    return r;
}

vector<int> poly_sub(const vector<int>& a, const vector<int>& b){
    vector<int> r(max(a.size(), b.size()));
    for(size_t i=0;i<r.size();++i){
        int av = i<a.size()?a[i]:0;
        int bv = i<b.size()?b[i]:0;
        r[i] = submod(av,bv);
    }
    return r;
}

vector<int> poly_trim(vector<int> a){ while(!a.empty() && a.back()==0) a.pop_back(); return a; }

vector<int> poly_scalar_mul(const vector<int>& a, int k){ vector<int> r(a.size()); for(size_t i=0;i<a.size();++i) r[i]=(long long)a[i]*k%MOD; return r; }

vector<int> poly_inv(const vector<int>& a, int n){
    vector<int> b(1, inv(a[0]));
    int cur = 1;
    while(cur < n){
        cur <<= 1;
        vector<int> a_cut(min((int)a.size(), cur));
        for(int i=0;i<(int)a_cut.size();++i) a_cut[i]=a[i];
        vector<int> nb = multiply(multiply(b,b), a_cut);
        b.resize(cur);
        for(int i=0;i<cur;i++){
            int val = i < (int)b.size() ? b[i] : 0;
            int sub = i < (int)nb.size() ? nb[i] : 0;
            b[i] = submod(addmod(val, val), sub);
        }
    }
    b.resize(n);
    return b;
}

vector<int> poly_divmod(const vector<int>& a, const vector<int>& b){
    vector<int> A = poly_trim(a);
    vector<int> B = poly_trim(b);
    int n = A.size(), m = B.size();
    if(n < m) return A;
    vector<int> Ar = A; reverse(Ar.begin(), Ar.end());
    vector<int> Br = B; reverse(Br.begin(), Br.end());
    int k = n - m + 1;
    vector<int> invBr = poly_inv(Br, k);
    vector<int> Ar_cut(Ar.begin(), Ar.begin()+k);
    vector<int> Qr = multiply(Ar_cut, invBr);
    Qr.resize(k);
    vector<int> Q = Qr; reverse(Q.begin(), Q.end());
    vector<int> BQ = multiply(B, Q);
    vector<int> R = poly_sub(A, BQ);
    R.resize(m-1);
    return poly_trim(R) ;
}

struct MultiEval{
    int m;
    vector<vector<int>> tree; // polynomials
    MultiEval(const vector<int>& points){
        m = points.size();
        tree.resize(4*max(1,m));
        if(m>0) build(1,0,m-1,points);
    }
    void build(int node, int l, int r, const vector<int>& pts){
        if(l==r){
            tree[node] = { (MOD - pts[l])%MOD, 1 };
        } else {
            int mid=(l+r)/2;
            build(node<<1, l, mid, pts);
            build(node<<1|1, mid+1, r, pts);
            tree[node] = multiply(tree[node<<1], tree[node<<1|1]);
        }
    }
    void evaluate_rec(const vector<int>& P, int node, int l, int r, vector<int>& out){
        vector<int> R = poly_divmod(P, tree[node]);
        if(l==r){
            out[l] = R.empty() ? 0 : R[0];
            return;
        }
        int mid=(l+r)/2;
        evaluate_rec(R, node<<1, l, mid, out);
        evaluate_rec(R, node<<1|1, mid+1, r, out);
    }
    vector<int> evaluate(const vector<int>& P){
        vector<int> out(m);
        if(m==0) return {};
        evaluate_rec(P,1,0,m-1,out);
        return out;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    if(!(cin>>N>>M)) return 0;
    vector<int> S(N);
    for(int i=0;i<N;i++){ long long x; cin>>x; S[i]=x%MOD; }
    vector<pair<int,long long>> ops(M);
    for(int i=0;i<M;i++){
        int t; cin>>t;
        if(t==1){ long long x; cin>>x; ops[i]={1, x%MOD}; }
        else ops[i]={2, 0};
    }
    long long sumS = 0; for(int v:S) sumS = (sumS + v) % MOD;

    function<vector<int>(int,int)> buildP = [&](int l, int r)->vector<int>{
        if(l==r) return vector<int>{S[l]%MOD, 1};
        int mid=(l+r)/2;
        auto L = buildP(l,mid);
        auto R = buildP(mid+1,r);
        return multiply(L,R);
    };
    vector<int> P = buildP(0,N-1);
    vector<int> Pd(P.size()?P.size()-1:0);
    for(size_t i=1;i<P.size();++i) Pd[i-1] = (long long)P[i]*i % MOD;

    vector<int> a_v(M), b_v(M), c_v(M), d_v(M);
    int a=1,b=0,c=0,d=1;
    vector<int> need_t_idx(M, -1);
    vector<int> points; points.reserve(M);
    for(int i=0;i<M;i++){
        if(ops[i].first==1){ int X = ops[i].second; a = (a + (long long)X * c) % MOD; b = (b + (long long)X * d) % MOD; }
        else { swap(a,c); swap(b,d); }
        a_v[i]=a; b_v[i]=b; c_v[i]=c; d_v[i]=d;
        if(c!=0){ int t = (long long)d * inv(c) % MOD; need_t_idx[i]=points.size(); points.push_back(t); }
    }

    vector<int> Pvals, Pdvals;
    if(!points.empty()){
        MultiEval me(points);
        Pvals = me.evaluate(P);
        Pdvals = me.evaluate(Pd);
    }

    a=1;b=0;c=0;d=1;
    for(int i=0;i<M;i++){
        if(ops[i].first==1){ int X = ops[i].second; a = (a + (long long)X * c) % MOD; b = (b + (long long)X * d) % MOD; }
        else { swap(a,c); swap(b,d); }
        if(c==0){
            int invd = inv(d);
            long long term1 = (long long)a * invd % MOD * sumS % MOD;
            long long term2 = (long long)N * (long long)b % MOD * invd % MOD;
            long long ans = (term1 + term2) % MOD;
            cout << ans << '\n';
        } else {
            int idx = need_t_idx[i];
            int P_t = Pvals[idx];
            int Pd_t = Pdvals[idx];
            int S_t = (long long)Pd_t * inv(P_t) % MOD;
            int invc = inv(c);
            long long term1 = (long long)N * a % MOD * invc % MOD;
            long long det = ((long long)a * d - (long long)b * c) % MOD; if(det<0) det+=MOD;
            long long invc2 = (long long)invc * invc % MOD;
            long long term2 = det * invc2 % MOD * S_t % MOD;
            long long ans = (term1 - term2) % MOD; if(ans<0) ans+=MOD;
            cout << ans << '\n';
        }
    }
    return 0;
}