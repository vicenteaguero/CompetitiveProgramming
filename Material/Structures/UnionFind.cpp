#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; i++)

struct UF
{
    int numSets;
    vector<int> p, rank, setSize;
    UF(int n)
    {
        numSets = n;
        setSize.assign(n, 1);
        rank.assign(n, 0);
        p.resize(n);
        rep(i, n) p[i] = i;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j)
    {
        if (isSameSet(i, j)) return;
        numSets--;
        int x = findSet(i), y = findSet(j);
        if (rank[x] > rank[y]) p[y] = x, setSize[x] += setSize[y];
        else p[x] = y, setSize[y] += setSize[x];
        if (rank[x] == rank[y]) rank[y]++;
    }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};