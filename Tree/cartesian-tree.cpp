// verified with:
// https://judge.yosupo.jp/submission/109768
// https://atcoder.jp/contests/abc255/submissions/35950420

template<typename T>
struct cartesian_tree{
  vector<int> L,R,par;

  explicit cartesian_tree(int _n, vector<T> _a): n(_n),val(_a) {
    L.assign(n,-1);
    R.assign(n,-1);
    par.assign(n,-1);
    path.reserve(n);
    for (int i = 0; i < n; ++i){
      int ko = -1;
      while(!path.empty() && val[i] < val[path.end()[-1]]){
        ko = path.end()[-1];
        path.pop_back();
      }
      if (ko != -1){
        par[ko] = i;
      }
      if (!path.empty()) par[i] = path.end()[-1];
      path.pb(i);
    }
    for(int i = 0; i < n; ++i){
      if (par[i] == -1) {
        par[i] = i; // ここは根の親の定義に依存
        continue;
      }
      if (i < par[i]){
        L[par[i]] = i;
      }else{
        R[par[i]] = i;
      }
    }
  }
  
  private:
    const int n;
    const vector<T> val;
    vector<int> path;
};