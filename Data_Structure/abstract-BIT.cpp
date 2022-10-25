// verified with:
// https://judge.yosupo.jp/submission/103510
// https://atcoder.jp/contests/arc033/submissions/34688335
// https://atcoder.jp/contests/abc185/submissions/34685459
// https://atcoder.jp/contests/chokudai_S001/submissions/34685918

#include<bits/stdc++.h>
using namespace std;

// 内部は1-indexだが、関数の引数は0-index
template<typename T>
struct BIT{
  BIT() : n(0) {}
  explicit BIT(int _n, function<T(T,T)> _fx, function<T(T)> _rev, T _ex) : n(_n+1),vec(_n+1,0),fx(_fx),rev(_rev),ex(_ex) {}
  
  // 加算 <O(logn)>
  void add(int i, T x){
    ++i;
    while(i < n){
      vec[i] = fx(vec[i],x);
      i += i&(-i);
    }
  }

  // 累積和[0,i) <O(logn)>
  T sum(int i){
    if(i == 0) return 0;
    T ret = ex;
    while(i > 0){
      ret = fx(vec[i],ret);
      i -= i&(-i);
    }
    return ret;
  }

  // 区間和[l,r) <O(logn)>
  T query(int l, int r){
    return fx(sum(r),rev(sum(l)));
  }

  // 累積和のlower_bound() <O(logn)>
  int binary_search(T x){
    int ret = 0, r = 1;
    while(r < n) r = r << 1;
    while(r > 0){
      if(ret+r < n && vec[ret+r] < x){
        x = fx(x,rev(vec[ret+r]));
        ret += r;
      }
      r = r >> 1;
    }
    return ret;
  } 

  private:
    int n;   // 頂点の個数
    vector<T> vec;
    function<T(T,T)> fx;   // 二項演算
    function<T(T)> rev;   // 逆元を返す
    const T ex;   // 単位元
};