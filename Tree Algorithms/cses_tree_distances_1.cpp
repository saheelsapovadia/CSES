#include <bits/stdc++.h>

using namespace std;
#define long long ll

int depth[200001];
int dist[200001];
vector<int> tree[200001];

int eval(int src, int par){
    int res=0;
    for(int child: tree[src]){
        if(child != par)
            res = max(res, 1 + eval(child, src));
    }
    return depth[src] = res;
}

void solve(int src, int par, int par_ans)
{
    vector<int> prefixMax, suffixMax;
    // get depth of child nodes.
    for(int child : tree[src])
    {
        if(child != par)
        {
            prefixMax.push_back(depth[child]);
            suffixMax.push_back(depth[child]);
        }
    }
    // build prefix and suffix
    for(int i = 1; i < prefixMax.size(); i++)
        prefixMax[i] = max(prefixMax[i], prefixMax[i-1]);
    for(int i = (int)suffixMax.size() - 2; i >= 0; i--)
        suffixMax[i] = max(suffixMax[i], suffixMax[i+1]);
 
    //eval ans for every child c_no
    int c_no = 0;
    for(int child : tree[src])
    {
        if(child != par)
        {
            int op1 = (c_no == 0) ? INT_MIN : prefixMax[c_no - 1];
            int op2 = (c_no == (int)suffixMax.size() - 1) ? INT_MIN : suffixMax[c_no + 1];
            int partial_ans = 1 + max(par_ans, max(op1,op2));
 
            solve(child, src, partial_ans);
            c_no++;
        }
    }
 
    //eval ans for src
    dist[src] = 1 + max(par_ans, (prefixMax.empty() ? -1 : prefixMax.back()));
}

int main() {
    int n;
    cin>> n;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    eval(1,0);
    solve(1,0,-1);
    for(int i = 1;i <= n;i++)
        cout<<dist[i]<<" ";
}