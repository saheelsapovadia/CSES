#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fr(a,b) for(int i = a; i < b; i++)
#define rep(i,a,b) for(int i = a; i < b; i++)
#define mod 1000000007
#define inf (1LL<<60)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define triplet pair<ll,pair<ll,ll>>
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
using namespace std;

vector<int> tree[200001];
int subnodes[200001];
ll subans[200001];
ll ans[200001];


void eval(int src, int par){
    int num=1;
    ll ans=0;
    for(int child: tree[src]){
        if(child!=par){
            eval(child,src);
            num+=subnodes[child];
            ans+= subnodes[child] + subans[child];
        }
    }
    subans[src]=ans;
    subnodes[src]=num;
}

void solve(int src, int par, ll par_ans, int& total){
    ans[src] = subans[src] + par_ans + total - subnodes[src];

    for(int child: tree[src]){
        if(child!=par){
            solve(child, src, ans[src] - (subans[child]+subnodes[child]), total);
        }
    }
}

int main() {
    int n;
    cin>> n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    eval(1,0);
    solve(1,0,0,n);
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
}