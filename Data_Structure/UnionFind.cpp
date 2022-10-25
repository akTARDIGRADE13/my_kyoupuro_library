// verified with:
// https://judge.yosupo.jp/submission/103478

#include<bits/stdc++.h>
using namespace std;

// αはアッカーマンの逆関数
struct UnionFind{
  UnionFind() : n(0) {}
  explicit UnionFind(int n) : n(n),parents(n,-1) {}
  
  // 頂点xと頂点yをmerge <ならしO(α(n))>
  void merge(int x, int y){
    x = root(x), y = root(y);
    if (x == y) return;
    if (parents[x] > parents[y]) swap(x,y);
    parents[x] += parents[y];
    parents[y] = x;
  }

  // 頂点xと頂点yが連結か否かを判定 <ならしO(α(n))>
  bool same(int x, int y){
    return root(x) == root(y);
  }

  // 頂点xの親を返す <ならしO(α(n))>
  int root(int x){
    if (parents[x] < 0){
      return x;
    }else{
      return parents[x] = root(parents[x]);
    }
  }

  // 頂点xが属する連結成分の大きさを返す <ならしO(α(n))>
  int size(int x){
    return -parents[root(x)];
  }
  
  // 連結成分ごとにまとめて返す <ならしO(n)>
  vector<vector<int>> groups(){
    vector<vector<int>> ret(n);
    vector<int> cnt(n),roots(n);
    for(int i = 0; i < n; ++i) {
      roots[i] = root(i);
      ++cnt[roots[i]];
    }
    for(int i = 0; i < n; ++i) ret[i].reserve(cnt[i]);
    for(int i = 0; i < n; ++i) ret[roots[i]].push_back(i);
    ret.erase(remove_if(ret.begin(), ret.end(), [&](const std::vector<int>& i) {return i.empty();}), ret.end());
    return ret;
  }

  private:
    // 頂点の個数
    int n;
    // 負なら連結成分の大きさ、非負なら親
    vector<int> parents;  
};
