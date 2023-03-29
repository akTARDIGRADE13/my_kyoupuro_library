// verified with:
// https://atcoder.jp/contests/code-thanks-festival-2017-open/submissions/40153584
// https://atcoder.jp/contests/agc002/submissions/40153598

#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct PartialPersistentArray {
  vector<vector<T>> array;
  vector<vector<int>> times;
 
  PartialPersistentArray(){}
  explicit PartialPersistentArray(vector<T> &arr, int t = 0){
    for(T &i:arr){
      array.push_back(vector<T>(0));
      array.end()[-1].push_back(i);
      times.push_back(vector<int>(0));
      times.end()[-1].push_back(t);
    }
  }
 
  void set_vec(vector<T> &arr, int t = 0) {
    for(T &i:arr){
      array.push_back(vector<T>(0));
      array.end()[-1].push_back(i);
      times.push_back(vector<int>(0));
      times.end()[-1].push_back(t);
    }
  }
 
  int size(){
    return (int)array.size();
  }
 
  bool exist(int idx, int t){
    if(idx >= size()) return false;
    return times[idx][0] <= t; 
  }
 
  void add(T &val, int t){
    array.push_back(vector<T>(0));
    array.end()[-1].push_back(val);
    times.push_back(vector<int>(0));
    times.end()[-1].push_back(t);
  }
 
  void update(T &val, int idx, int t){
    array[idx].push_back(val);
    times[idx].push_back(t);
  }
 
  T get(int idx, int t){
    assert(exist(idx,t));
    if(times[idx].end()[-1] <= t){
      return array[idx].end()[-1];
    }
    int i = upper_bound(times[idx].begin(),times[idx].end(),t)-times[idx].begin();
    return array[idx][i-1];
  }
};