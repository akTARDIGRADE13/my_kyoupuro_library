// verified with:
// https://judge.yosupo.jp/submission/109990
// https://judge.yosupo.jp/submission/109991
// https://atcoder.jp/contests/abc254/submissions/35985098

#include<bits/stdc++.h>
using namespace std;

// RMQ <int>
// auto fx = [](int x1,int x2) -> int{ return min(x1,x2);}
// int ex = INT_MAX
template <typename T>
struct segment_tree{
  explicit segment_tree(int _n, function<T(T,T)> _fx, T _ex) : fx(_fx), ex(_ex) {
    n = 1;
    while (n < _n) n *= 2;
    val.assign(n*2,ex);
  }

  void set_vec(vector<T> a){
    for(int i = 0; i < (int)a.size(); ++i) val[i+n] = a[i];
    for(int i = n-1; i > 0; --i) val[i] = fx(val[i<<1],val[(i<<1)|1]);
  }

  void add(int i,T x){
    i += n;
    val[i] = fx(val[i],x);
    i >>= 1;
    while(i){
      val[i] = fx(val[i<<1],val[(i<<1)|1]);
      i >>= 1;
    }
  }

  void update(int i,T x){
    i += n;
    val[i] = x;
    i >>= 1;
    while(i){
      val[i] = fx(val[i<<1],val[(i<<1)|1]);
      i >>= 1;
    }
  }

  T query(int l,int r){
    T vl = ex,vr = ex;
    l += n;
    r += n;
    while(l < r) {
      if(l&1) vl = fx(vl,val[l++]);
      if(r&1) vr = fx(val[--r],vr);
      l >>= 1;
      r >>= 1;
    }
    return fx(vl,vr);
  }

  private:
    int n;
    vector<T> val;
    function<T(T,T)> fx;
    const T ex;
};