#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

#define rep(i, n) for (int i = 0; i < (int)n; i++)
typedef set<pair<int, int>>::iterator iter;

int N, Q, S, T, X, D;
set<pair<int, pair<int, int>>> events;
multiset<int> active;
vi ans;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> Q;

    rep(i, N)
    {
        cin >> S >> T >> X;
        events.insert({T - X, {0, X}});
        events.insert({S - X, {1, X}});

        if (S - X < 0 && T - X >= 0)
            active.insert(X);
    }

    rep(i, Q)
    {
        cin >> D;
        events.insert({D, {2, i}});
    }

    ans.assign(Q, -1);

    for (auto e : events)
    {
        T = e.second.first;
        X = e.second.second;

        if (T == 0)
            active.erase(X);
        if (T == 1)
            active.insert(X);
        if (T == 2)
            if (!active.empty())
                ans[X] = *active.begin();
    }

    rep(i, Q) cout << ans[i] << '\n';
}