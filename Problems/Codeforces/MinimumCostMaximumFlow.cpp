#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; i++)
typedef long long ll;

template <class T>
class MCMF
{
public:
	struct Edge
	{
		Edge(int a, T b, T c) : to(a), cap(b), cost(c) {}
		int to;
		T cap, cost;
	};

	MCMF(int size)
	{
		n = size;
		edges.resize(n);
		pot.assign(n, 0);
		dist.resize(n);
		visit.assign(n, false);
	}

	pair<T, T> mcmf(int src, int sink)
	{
		pair<T, T> ans(0, 0);
		if (!SPFA(src, sink))
			return ans;
		fixPot();
		while (SPFA(src, sink))
		{
			auto flow = augment(src, sink);
			ans.first += flow.first;
			ans.second += flow.first * flow.second;
			fixPot();
		}
		return ans;
	}

	void addEdge(int from, int to, T cap, T cost)
	{
		edges[from].push_back(list.size());
		list.push_back(Edge(to, cap, cost));
		edges[to].push_back(list.size());
		list.push_back(Edge(from, 0, -cost));
	}

private:
	int n;
	vector<std::vector<int>> edges;
	vector<Edge> list;
	vector<int> from;
	vector<T> dist, pot;
	vector<bool> visit;

	pair<T, T> augment(int src, int sink)
	{
		pair<T, T> flow = {list[from[sink]].cap, 0};
		for (int v = sink; v != src; v = list[from[v] ^ 1].to)
		{
			flow.first = min(flow.first, list[from[v]].cap);
			flow.second += list[from[v]].cost;
		}
		for (int v = sink; v != src; v = list[from[v] ^ 1].to)
		{
			list[from[v]].cap -= flow.first;
			list[from[v] ^ 1].cap += flow.first;
		}
		return flow;
	}

	queue<int> q;
	bool SPFA(int src, int sink)
	{
		T INF = std::numeric_limits<T>::max();
		dist.assign(n, INF);
		from.assign(n, -1);
		q.push(src);
		dist[src] = 0;
		while (!q.empty())
		{
			int on = q.front();
			q.pop();
			visit[on] = false;
			for (auto e : edges[on])
			{
				auto ed = list[e];
				if (ed.cap == 0)
					continue;
				T toDist = dist[on] + ed.cost + pot[on] - pot[ed.to];
				if (toDist < dist[ed.to])
				{
					dist[ed.to] = toDist;
					from[ed.to] = e;
					if (!visit[ed.to])
					{
						visit[ed.to] = true;
						q.push(ed.to);
					}
				}
			}
		}
		return dist[sink] < INF;
	}

	void fixPot()
	{
		T INF = numeric_limits<T>::max();
		for (int i = 0; i < n; i++)
			if (dist[i] < INF)
				pot[i] += dist[i];
	}
};

int n, m, u, v;
ll cap, cost;

int main()
{
	cin >> n >> m;

	MCMF<ll> mcmf(n);
	rep(i, m)
	{
		cin >> u >> v >> cap >> cost;
		mcmf.addEdge(u - 1, v - 1, cap, cost);
	}

	cout << mcmf.mcmf(0, n - 1).second << '\n';
}