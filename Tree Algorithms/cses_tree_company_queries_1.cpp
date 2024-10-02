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
int par[200001];
int LOG = 21;
vector<vector<int>> up(200001,vector<int>(LOG, 0));
vector<int> depth(200001,0);
void eval(int n){
    par[0]=0;
    depth[0]=-1;
    for(int i=0;i<=n;i++){
        up[i][0]=par[i];
        if(i!=0) depth[i]=depth[par[i]]+1;
        for(int j=1;j<LOG;j++){
            up[i][j]=up[up[i][j-1]][j-1];
        }
        // cout<<"depth"<<i<<" "<<depth[i]<<endl;
    }
}

int main() {
    int n, q;
    cin>> n >> q;
    for(int i=2;i<=n;i++){
        int u;
        cin>>u;
        par[i]=u;
    }
    eval(n);
    for(int i=0;i<q;i++){
        int node,k;
        cin>>node>>k;
        // cout<<node<<" "<<depth[node]<<endl;
        if(k > depth[node]){
            cout<<-1<<endl;
            continue;
        }
        for(int j=0;j<LOG;j++){
            if(k & (1 << j))
                node = up[node][j];
        }
        cout<<node<<endl;
    }
}