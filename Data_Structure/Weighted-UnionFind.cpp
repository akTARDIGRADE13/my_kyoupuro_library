// verified with:
// https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_1_B
// https://atcoder.jp/contests/abc087/submissions/39744954
// https://atcoder.jp/contests/abc280/submissions/39745774

#include<bits/stdc++.h>
using namespace std;


template<typename T>
struct Weighted_UnionFind{
  Weighted_UnionFind() : n(0) {}
  explicit Weighted_UnionFind(int n, function<T(T,T)> _fx, function<T(T)> _inv, T _ex) : n(n), fx(_fx), inv(_inv){
    parents.assign(n,-1);
    potential.assign(n,_ex);
  }
  
  bool merge(int x, int y, T w){
    w += weight(x); w -= weight(y);
    x = root(x), y = root(y);

    // 既に同じ集合に属しているときの処理
    if (x == y) {
      // 矛盾が無ければtrue、あればfalse
      if (diff(x,y) == w){
        return true;
      }else{
        return false;
      }
    }

    if (parents[x] > parents[y]) swap(x,y), w = inv(w);
    parents[x] += parents[y];
    parents[y] = x;
    potential[y] = w;
		return true;
  }

  bool same(int x, int y){
    return root(x) == root(y);
  }

  int root(int x){
    if (parents[x] < 0){
      return x;
    }else{
      int r = root(parents[x]);
      potential[x] = fx(potential[x],potential[parents[x]]);
      return parents[x] = r;
    }
  }

  int size(int x){
    return -parents[root(x)];
  }

  T weight(int x){
    root(x);
    return potential[x];
  }

  T diff(int x, int y) {
    return fx(weight(y),inv(weight(x)));
  }
  
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
    const int n;
    vector<int> parents;
    vector<T> potential;
		function<T(T,T)> fx;
		function<T(T)> inv;
};