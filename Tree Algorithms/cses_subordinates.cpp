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
    int c=0;
    for(int child: tree[src]){
        if(child != par){
            cd.push_back(downpath[child]);
            res += solve(child, src) + 1;
            c++;
        }
    }
    return diameter[src] = res;
};

int main() {
    int n;
    cin>> n;
    
    for(int i=2;i<n+1;i++){
        int u;
        cin>>u;
        tree[u].push_back(i);
    }

    solve(1,0);
    for(int i=1;i<n+1;i++)
        cout<<diameter[i]<<" ";
}