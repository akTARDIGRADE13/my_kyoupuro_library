// verified with:
// https://atcoder.jp/contests/code-thanks-festival-2017-open/submissions/40153584
// https://atcoder.jp/contests/agc002/submissions/40153598

// PartialPersistentArrayのライブラリを要求
struct PartialPersistentUnionFind{
  PartialPersistentUnionFind() : n(0){}
  explicit PartialPersistentUnionFind(int n) : n(n) {
    vector<int> p(n,-1);
    parents.set_vec(p);
    cnt_uni.emplace_back(n);
    times.push_back(0);
  }
  
  void merge(int x, int y, int t){
    x = root(x), y = root(y);
    if (x == y) return;
    int sx = parents.get(x,t), sy = parents.get(y,t) ,sxy = sx+sy;
    if (sx > sy) {
      parents.update(sxy, y, t);
      parents.update(y, x, t);
    } else {
      parents.update(sxy, x, t);
      parents.update(x, y, t);
    }
    cnt_uni.push_back(cnt_uni.end()[-1]-1);
    times.push_back(t);
  }

  bool same(int x, int y, int t = 1<<30){
    return root(x,t) == root(y,t);
  }

  int count_groups(int t){
    assert(t >= 0);
    if(cnt_uni.end()[-1] <= t){
      return cnt_uni.end()[-1];
    }
    int i = upper_bound(times.begin(),times.end(),t)-times.end();
    return cnt_uni[i-1];
  }

  int root(int x, int t = 1<<30){
    if (parents.get(x,t) < 0){
      return x;
    }else{
      return root(parents.get(x,t),t);
    }
  }

  int size(int x, int t = 1<<30){
    return -parents.get(root(x,t),t);
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
    // 頂点の個数
    int n;
    // 負なら連結成分の大きさ、非負なら親
    PartialPersistentArray<int> parents;  
    // 連結成分の個数
    vector<int> cnt_uni;
    vector<int> times;
};