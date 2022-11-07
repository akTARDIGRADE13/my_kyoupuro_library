// verified with:
// https://atcoder.jp/contests/abc253/submissions/36002462

#include<bits/stdc++.h>
using namespace std;

// 内部は1-indexだが、関数の引数は0-index
template<typename T>
struct range_BIT{
  range_BIT() : n(0) {}
  explicit range_BIT(int _n) : n(_n+2),vec(2,vector<T>(_n+2,0)) {}
  
  // 加算(半開区間) <O(logn)>
  void add(int l, int r, T x){
    ++l,++r;
    for (int i = l; i < n; i += i&(-i)) {
      vec[0][i] -= x*(l-1);
      vec[1][i] += x;
    }
    for (int i = r; i < n; i += i&(-i)) {
      vec[0][i] += x*(r-1);
      vec[1][i] -= x;
    }
  }
 
  // 累積和[0,i) <O(logn)>
  T sum(int i){
    T ret(0);
    int k = i;
    while (i > 0){
      ret += vec[1][i]*k+vec[0][i];
      i -= i&(-i);
    }
    return ret;
  }
 
  // 区間和[l,r) <O(logn)>
  T query(int l, int r){
    return sum(r)-sum(l);
  }
 
  private:
    int n;
    vector<vector<T>> vec;
};