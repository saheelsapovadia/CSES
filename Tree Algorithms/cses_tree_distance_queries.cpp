#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define fr(a, b) for (int i = a; i < b; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define mod 1000000007
#define inf (1LL << 60)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define triplet pair<ll, pair<ll, ll>>
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL)
using namespace std;

vector<int> tree[200001];
int par[200001];
int LOG = 21;
int up[21][200001];
int depth[200001];


void dfs(int src, int par, int d)
{
    up[0][src] = par;
    depth[src] = d;
    for (int child : tree[src])
        if (child != par)
            dfs(child, src, d + 1);
}

void eval(int n)
{
    dfs(1, -1, 0);
    for (int j = 1; 1 << j <= n; j++)
    {
        for (int i = 0; i <= n; i++)
        {
            up[j][i] = up[j - 1][up[j-1][i]];
        }
    }
}

void preprocess_LCA(int n) {	
	dfs(1, -1, 0);
		
	for (int i = 1; 1<<i <= n ; i++) 
	for (int j = 0; j <= n ; j++)
	up[i][j] = up[i-1][up[i-1][j]];
}

int getKthNode(int node, int k)
{
    for (int j = LOG; j >= 0; j--)
    {
        if (k & (1 << j))
            node = up[j][node];
    }
    return node;
}


int getLCA(int u, int v)
{
    if (depth[u] > depth[v])
        swap(u, v);
    int diff = depth[v] - depth[u];
    v = getKthNode(v, diff);
    if (u == v)
        return u;

    for (int j = 20; j >= 0; j--)
    {
        if (up[j][v] != up[j][u])
        {
            v = up[j][v];
            u = up[j][u];
        }
    }
    return up[0][v];
}

int main()
{
    int n, q, u, v, a, b;
    cin >> n >> q;
    int k = n - 1;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    preprocess_LCA(n);

    while (q--)
    {
        cin >> a >> b;
        int l = getLCA(a, b);
        cout << (depth[a] + depth[b] - 2 * depth[l]) << endl;
    }
}