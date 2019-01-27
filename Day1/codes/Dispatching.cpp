#include <bits/stdc++.h>
#define ri register int
#define il inline
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int maxn = 1e5 + 110;
const int maxm = 110;
const int inf = 0x7fffffff;
const double eps = 1e-8;

il int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch))
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch))
	{
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar();
	}
	return x * f;
}

il ll chkmax(ll a, ll b)
{
	return a > b ? a : b;
}

int n, m;
int l[maxn], fa[maxn], rt[maxn], siz[maxn];
ll ans, sum[maxn];

namespace Leftist_Tree
{
	struct node
	{
		int val, dis;
		int ls, rs;
	};
	node a[maxn];

	il int Merge(int x, int y)
	{
		if (!x || !y)
			return x + y;
		if (a[x].val < a[y].val)
			swap(x, y);
		a[x].rs = Merge(a[x].rs, y);
		fa[a[x].rs] = x;
		if (a[a[x].ls].dis < a[a[x].rs].dis)
			swap(a[x].ls, a[x].rs);
		a[x].dis = a[a[x].rs].dis + 1;
		return x;
	}

	il int Delete(int x)
	{
		fa[a[x].ls] = fa[a[x].rs] = fa[x] = 0;
		int ret = Merge(a[x].ls, a[x].rs);
		a[x].ls = a[x].rs = 0;
		return ret;
	}
}
using namespace Leftist_Tree;

struct Graph
{
	int cnt, head[maxn];

	struct edge
	{
		int to, nxt;
	};
	edge e[maxn << 1];

	il void add_edge(int u, int v)
	{
		e[++cnt] = (edge) {v, head[u]};
		head[u] = cnt;
	}
	il void Link(int u, int v)
	{
		add_edge(u, v);
		add_edge(v, u);
	}
};
Graph G;

il void DFS(int x)
{
	rt[x] = x, sum[x] = a[x].val, siz[x] = 1;
	for (ri i = G.head[x]; i; i = G.e[i].nxt)
	{
		int v = G.e[i].to;
		DFS(v);
		sum[x] += sum[v];
		siz[x] += siz[v];
		rt[x] = Merge(rt[x], rt[v]);
	}
	while (sum[x] > m)
	{
		sum[x] -= a[rt[x]].val, siz[x]--;
		rt[x] = Delete(rt[x]);
	}
	ans = chkmax(ans, 1ll * siz[x] * l[x]);
}

int main()
{
	n = read(), m = read();
	for (ri i = 1; i <= n; i++)
	{
		fa[i] = read();
		a[i].val = read();
		l[i] = read();
		G.add_edge(fa[i], i);
	}
	DFS(1);
	printf("%lld", ans);
	return 0;
}
/*
5 4
0 3 3
1 3 5
2 2 2
1 2 4
2 3 1

10 1000000000
0 1 99007575
1 2 438573466
1 2 1000000000
1 1 353443732
1 2 291838734
1 1 248014694
1 1 147944159
1 2 299181667
1 1 276916145
5 1 155026402

*/
