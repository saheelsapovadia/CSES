#include <bits/stdc++.h>

using namespace std;
#define long long ll

int dp[200001][2];
vector<int> tree[200001];

void solve(int src, int par){
    vector<int> prefix, suffix;
    dp[src][0]=dp[src][1] = 0;
    int c=0;
    
    for(int child: tree[src]){
        if(child!=par){
            solve(child,src);
            c++;
        }
    }

    if(c==0) return;
    
    for(int child:tree[src]){
        if(child!=par){
            prefix.push_back(max(dp[child][0], dp[child][1]));
            suffix.push_back(max(dp[child][0], dp[child][1]));
        }
    }

    for(int i=1;i<prefix.size();i++){
        prefix[i]+=prefix[i-1];
    }
    for(int i=suffix.size()-2;i>=0;i--){
        suffix[i]+=suffix[i+1];
    }

    dp[src][0]=suffix[0];
    int i=0;
    for(int child:tree[src]){
        if(child!=par){
            int l = i==0 ? 0 : prefix[i-1];
            int r = i==suffix.size()-1 ? 0 : suffix[i+1];
            dp[src][1]=max(dp[src][1], 1 + l + r + dp[child][0]);
            i++;
        }
    }
};

int main() {
    int n;
    cin>> n;
    
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    solve(1,0);
    cout<<max(dp[1][0], dp[1][1]);
}