#include<bits/stdc++.h>
using namespace std;

struct LowLink{
  vector<int> aps;
  vector<pair<int,int>> bridges;
 
  explicit LowLink(int _n,vector<vector<int>> _G): n(_n),G(_G) {
    seen.assign(n,false);
    check_aps.assign(n,false);
    ord.assign(n,0);
    low.assign(n,0);
    int k = 0;
    for(int i = 0;i < n;++i){
      if (!seen[i]) dfs(i,-1,k);
    }
    sort(aps.begin(),aps.end());
    sort(bridges.begin(),bridges.end());
  }
 
  void dfs(int now,int par,int &k){
    seen[now] = true;
    int count = 0;
    ord[now] = k++;
    low[now] = ord[now];
    for(int i:G[now]){
      if (i == par) continue;
      if (seen[i]){
        low[now] = min(low[now],ord[i]);
      }else{
        ++count;
        dfs(i,now,k);
        low[now] = min(low[now],low[i]);
        if (par != 1 && ord[now] <= low[i]) check_aps[now] = true;
        if (ord[now] < low[i]) bridges.emplace_back(min(now,i),max(now,i));
      }
    }
    if (par == 1 && count >= 2) check_aps[now] = true;
    if (check_aps[now]) aps.push_back(now); 
  }
 
  bool is_aps(int x){
    return check_aps[x];
  }

  bool is_bridges(int x, int y){
    if (ord[x]>ord[y]) swap(x,y);
    return ord[x] < low[y];
  }
 
  private:
    const int n;
    const vector<vector<int>> G;
    vector<int> ord,low;
    vector<bool> seen,check_aps;
};