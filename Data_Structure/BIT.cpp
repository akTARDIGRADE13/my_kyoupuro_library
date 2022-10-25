// verified with:
// https://judge.yosupo.jp/submission/103536
// https://atcoder.jp/contests/arc033/submissions/34688064

#include<bits/stdc++.h>
using namespace std;

// 内部は1-indexだが、関数の引数は0-index
template<typename T>
struct BIT{
  BIT() : n(0) {}
  explicit BIT(int _n) : n(_n+1),vec(_n+1,0) {}
  
  // 加算 <O(logn)>
  void add(int i, T x){
    ++i;
    while (i < n){
      vec[i] += x;
      i += i&(-i);
    }
  }

  // 累積和[0,i) <O(logn)>
  T sum(int i){
    T ret(0);
    while (i > 0){
      ret += vec[i];
      i -= i&(-i);
    }
    return ret;
  }

  // 区間和[l,r) <O(logn)>
  T query(int l, int r){
    return sum(r)-sum(l);
  }

  // 累積和のlower_bound() <O(logn)>
  int binary_search(T x){
    int ret = 0, r = 1;
    while(r < n) r = r << 1;
    while (r > 0){
      if(ret+r < n && vec[ret+r] < x){
        x -= vec[ret+r];
        ret += r;
      }
      r = r >> 1;
    }
    return ret;
  } 

  private:
    int n;
    vector<T> vec;
};