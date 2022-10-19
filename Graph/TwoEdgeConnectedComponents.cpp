#include<bits/stdc++.h>
using namespace std;

struct TwoEdgeConnectedComponents{
  vector<vector<int>> groups;
  vector<int> idx;
 
  explicit TwoEdgeConnectedComponents(int _n,vector<vector<int>> _G): n(_n),G(_G) {
    seen.assign(n,false);
    check_aps.assign(n,false);
    ord.assign(n,0);
    low.assign(n,0);
    idx.assign(n,0);
    int k = 0;
    for(int i = 0;i < n;++i){
      if (!seen[i]) dfs(i,-1,k);
    }
    build();
  }

  void build(){
    seen.assign(n,false);
    int cnt = 0;
    queue<int> q;
    for(int i = 0;i < n;++i){
      if (seen[i]) continue;
      q.push(i);
      groups.push_back(vector<int>{});
      while(!q.empty()){
        int l = q.front();
        q.pop();
        if(seen[l]) continue;
        groups[cnt].push_back(l);
        idx[l] = cnt;
        seen[l] = true;
        for(int j:G[l]){
          if (seen[j]) continue;
          if (is_bridges(l,j)) continue;
          q.push(j);
        }
      }
      ++cnt;
    }
  }

  int get_idx(const int &k) {
    return idx[k];
  }
 
  void dfs(int now,int par,int &k){
    seen[now] = true;
    int count = 0;
    bool flag = true;
    ord[now] = k++;
    low[now] = ord[now];
    for(int i:G[now]){
      if (i == par && flag) {
        flag = false;
        continue;
      }
      if (seen[i]){
        low[now] = min(low[now],ord[i]);
      }else{
        ++count;
        dfs(i,now,k);
        low[now] = min(low[now],low[i]);
        if (par != 1 && ord[now] <= low[i]) check_aps[now] = true;
      }
    }
    if (par == 1 && count >= 2) check_aps[now] = true;
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