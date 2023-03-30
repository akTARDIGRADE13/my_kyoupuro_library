// verified with:
// https://atcoder.jp/contests/abc242/submissions/40170714
// https://atcoder.jp/contests/abc174/submissions/40170808
// https://atcoder.jp/contests/abc293/submissions/40171159

#include<bits/stdc++.h>
using namespace std;

template<typename T,typename ANS>
struct Mo {
  int n,q,width;
  vector<long long> data, query;
  vector<T> arr;
  vector<ANS> ans;

  explicit Mo(int _n, int _q, vector<T> &_arr) : n(_n), q(_q), arr(_arr), ans(_q){
    data = vector<long long>(_q);
    query = vector<long long>(_q);
    width = max<int>(1, 1.0*n/max<double>(1.0, sqrt(q * 2.0 / 3.0)));
  }

  // 半開区間
  void add(long long idx, long long l, long long r) {
    data[idx] = (l<<20)|r;
    l /= width;
    query[idx] = (l<<40) + (((l&1)?-r:r)<<20) + idx;
  }

  // 問題に合わせて書き換える--------------------------------------------------------------
  // 必要な変数を追加で定義してもよい
  void initProcess(){
  }

  void addR(int idx){
  }

  void addL(int idx){
    addR(idx);
  }

  void delR(int idx){
  }

  void delL(int idx){
    delR(idx);
  }

  void rec(int idx){
  }
  // ----------------------------------------------------------------------------------

  vector<ANS> solve(){
    sort(query.begin(),query.end());
    int nl = 0,nr = 0;
    int mask = (1<<20)-1;
    initProcess();
    for(int i:query){
      int idx = i&mask, l = data[idx]>>20, r = data[idx]&mask;
      while (nl > l) addL(--nl);
      while (nr < r) addR(nr++);
      while (nl < l) delL(nl++);
      while (nr > r) delR(--nr);
      rec(idx);
    }
    return ans;
  }
};