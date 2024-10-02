#include <bits/stdc++.h>

using namespace std;
#define long long ll

int downpath[200001];
int diameter[200001];
vector<int> tree[200001];

int eval(int src, int par){
    int res=0;
    for(int child: tree[src]){
        if(child != par)
        res=max(res, 1 + eval(child, src));
    }
    downpath[src]=res;
    return res;
}

int solve(int src, int par){
    int res=0;
    vector<int> cd;
    for(int child: tree[src]){
        if(child != par){
            cd.push_back(downpath[child]);
            res = max(res, solve(child, src));
        }
    }
    sort(cd.begin(),cd.end());
    int num=cd.size();
    if(num==0) diameter[src]=0;
    else if(num==1) diameter[src] = 1 + cd[0];
    else diameter[src] = 2 + cd[num-1] + cd[num-2];
    diameter[src]=max(res, diameter[src]);
    return diameter[src];
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

    eval(1,0);
    solve(1,0);
    cout<<diameter[1];
}