#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> par;
typedef vector<ll> vi;
typedef vector<par> vp;
typedef vector<vi> graph;
typedef vector<vp> wgraph;

#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = a; i < (int)b; i++)
#define invrep(i, a, b) for (int i = b; i-- > (int)a;)

#define pb push_back
#define eb emplace_back
#define ppb pop_back

#define umap unordered_map

#define lg(x) (31 - __buitlin_clz(x))
#define lgg(x) (63 - __buitlin_clzll(x))
#define gcd __gcd

//ios::sync_with_stdio(0); cin.tie(0);
//cout.setf(ios::fixed); cout.precision(4);

#define debugx(x) cerr << #x << ": " << x << endl
#define debugv(v)  //        \
    cerr << #v << ":";    \
    for (auto e : v)      \
        cerr << " " << e; \
    cerr << endl
#define debugm(m)  //                                      \
    cerr << #m << endl;                                  \
    rep(i, (int)m.size())                                \
    {                                                    \
        cerr << i << ":";                                \
        rep(j, (int)m[i].size()) cerr << " " << m[i][j]; \
        cerr << endl;                                    \
    }
#define debugmp(m) //\
    cerr << #m << endl;                                                                         \
    rep(i, (int)m.size())                                                                       \
    {                                                                                           \
        cerr << i << ":";                                                                       \
        rep(j, (int)m[i].size()) cerr << " {" << m[i][j].first << "," << m[i][j].second << "}"; \
        cerr << endl;                                                                           \
    }
#define print(x) copy(x.begin(), x.end(), ostream_iterator<int>(cout, “”)), cout << endl

// definicion de Fenwick Tree sacada de cp-algorithms.

struct FenwickTree
{
    vector<ll> bit; // binary indexed tree
    int n;

    FenwickTree(int n)
    {
        this->n = n + 1;
        bit.assign(n + 1, 0);
    }

    ll sum(int idx)
    {
        ll ret = 0;
        for (; idx > 0; idx -= (idx & -idx))
            ret += bit[idx];
        return ret;
    }

    void add(int idx, ll delta)
    {
        for (; idx < n; idx += (idx & -idx))
            bit[idx] += delta;
    }

    void range_add(int l, int r, ll val)
    {
        add(l, val);
        add(r + 1, -val);
    }
};

int n, m, u, v, p;
ll c, k;
char t;

int main()
{

    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> c;
    FenwickTree ft(n);

    rep(i, m)
    {
        cin >> t;
        if (t == 'S')
        {
            cin >> u >> v >> k;
            ft.range_add(u, v, k);
        }
        if (t == 'Q')
        {
            cin >> p;
            cout << ft.sum(p) + c << '\n';
        }
    }
}