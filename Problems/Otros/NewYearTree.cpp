#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> par;
typedef vector<int> vi;
typedef vector<float> vfloat;
typedef vector<par> vp;
typedef vector<vi> graph;
typedef vector<vp> wgraph;

#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = a; i < (int)b; i++)
#define invrep(i, a, b) for (int i = b; i-- > (int)a;)

#define pb push_back
#define pf push_front
#define eb emplace_back
#define ppb pop_back

#define umap unordered_map

#define lg(x) (31 - __buitlin_clz(x))
#define lgg(x) (63 - __buitlin_clzll(x))
#define gcd __gcd

//ios::sync_with_stdio(0); cin.tie(0);
//cout.setf(ios::fixed); cout.precision(4);

#define debugx(x) cerr << #x << ": " << x << endl
#define debugv(v)         \
    cerr << #v << ":";    \
    for (auto e : v)      \
        cerr << " " << e; \
    cerr << endl
#define debugm(m)                                        \
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

// Lazy Segment Tree modificado de apuntes Ignacio Hermosilla.

template <class t>
class STL
{
    vector<ll> arr, st, lazy;
    int n;

    void build(int u, int i, int j)
    {
        if (i == j)
        {
            st[u] = arr[i];
            return;
        }
        int m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
        build(l, i, m);
        build(r, m + 1, j);
        st[u] = t::op(st[l], st[r]);
    }

    void propagate(int u, int i, int j, ll x)
    {
        // nota, las operaciones pueden ser un and, or, ..., etc.
        // st[u] += t::lazy_op(i, j, x); // incrementar el valor (+)
        st[u] = t::lazy_op(i, j, x); // setear el valor
        if (i != j)
        {
            // incrementar el valor
            // lazy[u * 2 + 1] += x;
            // lazy[u * 2 + 2] += x;
            // setear el valor
            lazy[u * 2 + 1] = x;
            lazy[u * 2 + 2] = x;
        }
        lazy[u] = 0;
    }

    ll query(int a, int b, int u, int i, int j)
    {
        if (j < a or b < i)
            return t::neutro;
        int m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
        if (lazy[u])
            propagate(u, i, j, lazy[u]);
        if (a <= i and j <= b)
            return st[u];
        ll x = query(a, b, l, i, m);
        ll y = query(a, b, r, m + 1, j);
        return t::op(x, y);
    }

    void update(int a, int b, ll value,
                int u, int i, int j)
    {
        int m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
        if (lazy[u])
            propagate(u, i, j, lazy[u]);
        if (a <= i and j <= b)
            propagate(u, i, j, value);
        else if (j < a or b < i)
            return;
        else
        {
            update(a, b, value, l, i, m);
            update(a, b, value, r, m + 1, j);
            st[u] = t::op(st[l], st[r]);
        }
    }

public:
    STL(vector<ll> &v)
    {
        arr = v;
        n = v.size();
        st.resize(n * 4 + 5);
        lazy.assign(n * 4 + 5, 0);
        build(0, 0, n - 1);
    }

    ll query(int a, int b)
    {
        return query(a, b, 0, 0, n - 1);
    }

    void update(int a, int b, ll value)
    {
        update(a, b, value, 0, 0, n - 1);
    }
};

struct RlQ
{
    static ll const neutro = 0;
    static ll op(ll x, ll y)
    {
        return (x | y);
    }
    static ll
    lazy_op(int i, int j, ll x)
    {
        return x;
    }
};

int n, m, a, b, t, v, c, turn;
vector<ll> colors;
vector<bool> visited;
graph g;
vector<ll> order;
vp ranges;

// DFS apuntes Pablo Messina.

void dfs(int u)
{
    visited[u] = true;
    for (int v : g[u])
    {
        if (!visited[v])
        {
            order.pb(colors[v]);
            ranges[v].first = turn;
            turn++;
            dfs(v);
            ranges[v].second = turn - 1;
        }
    }
}

int count(ll m)
{
    int count = 0;
    for (ll i = 0; i < 60; i++)
        if (((ll)1 << i) & m)
            count++;
    return count;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    colors.resize(n);
    g.resize(n);
    visited.assign(n, false);
    ranges.resize(n);
    turn = 0;

    rep(i, n)
    {
        cin >> c;
        colors[i] = (ll)1 << (c - 1);
    }

    rep(i, n - 1)
    {
        cin >> a >> b;
        g[a - 1].pb(b - 1);
        g[b - 1].pb(a - 1);
    }

    order.pb(colors[0]);
    ranges[0].first = turn;
    turn++;
    dfs(0);
    ranges[0].second = turn - 1;
    STL<RlQ> st(order);

    rep(i, m)
    {
        cin >> t;
        if (t == 1)
        {
            cin >> v >> c;
            st.update(ranges[v - 1].first, ranges[v - 1].second, (ll)1 << (c - 1));
        }
        else
        {
            cin >> v;
            cout << count(st.query(ranges[v - 1].first, ranges[v - 1].second)) << '\n';
        }
    }
}