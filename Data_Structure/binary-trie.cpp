// verified with:
// https://judge.yosupo.jp/submission/127704
// https://atcoder.jp/contests/arc033/submissions/39204919
// https://codeforces.com/group/zX1lm3q5cU/contest/665/submission/194980697
// https://atcoder.jp/contests/abc253/submissions/39204865

#include <bits/stdc++.h>
using namespace std;

template<typename T, int len>
struct BinaryTrie {
  BinaryTrie() : root(new Node), xor_value(0) {}
  
  void insert(T x, T cnt=1) {
    x ^= xor_value;
    Node* v = root;
    v->size += cnt;
    for(int i = len-1; i >= 0; --i){
      int b = (x>>i)&1;
      if(v->children[b] == nullptr){
        v->children[b] = new Node;
        v->children[b]->parent = v;
      }
      v = v->children[b];
      v->size += cnt;
    }
  }
  
  void erase(T x, T cnt=1) {
    Node* v = root;
    cnt = std::min(cnt,count(x));
    x ^= xor_value;
    if(!cnt) return;
    v->size -= cnt;
    for(int i = len-1; i >= 0; --i){
      int b = (x>>i)&1;
      v = v->children[b];
      v->size -= cnt;
    }
    for(int i = 0; i < len; ++i){
      if(v->size) break;
      auto p = v->parent;
      int b = (x>>i)&1;
      p->children[b] = nullptr;
      v->parent = nullptr;
      v = p;
    }
  }
  
  T count(T x) {
    Node* v = root;
    x ^= xor_value;
    for(int i = len-1; i >= 0; --i){
      int b = (x>>i)&1;
      if(v->children[b] == nullptr)
        return 0;
      v = v->children[b];
    }
    return v->size;
  }
  
  T kth_element(int k) {
    ++k;
    Node* v = root;
    T ret = 0;
    for(int i = len-1; i >= 0; --i){
      int b = (xor_value>>i)&1;
      if(v->children[b] == nullptr ||
         v->children[b]->size < k){
        if(v->children[b] != nullptr)
          k -= v->children[b]->size;
        b ^= 1;
      }
      ret <<= 1;
      ret |= b;
      v = v->children[b];
    }

    return ret^xor_value;
  }
  
  T count_leq(T x) {
    Node* v = root;
    T ret = 0;
    for(int i = len-1; i >= 0; --i){
      int b = ((xor_value^x)>>i)&1;
      int t = (x>>i)&1;
      if(t && v->children[b^1] != nullptr)
        ret += v->children[b^1]->size;
      if(v->children[b] == nullptr){
        return ret;
      }
      v = v->children[b];
    }
    return ret+v->size;
  }

  T count_geq(T x) {
    Node* v = root;
    T ret = 0;
    for(int i = len-1; i >= 0; --i){
      int b = ((xor_value^x)>>i)&1;
      int t = (x>>i)&1;
      if((!t) && v->children[b^1] != nullptr)
        ret += v->children[b^1]->size;
      if(v->children[b] == nullptr){
        return ret;
      }
      v = v->children[b];
    }
    return ret+v->size;
  }
  void xor_all(T x) {
    xor_value ^= x;
  }
  T size() {
    return root->size;
  }
  T max() {
    return kth_element(size()-1);
  }
  T min() {
    return kth_element(0);
  }

  private:
    struct Node {
      T size;
      Node* parent;
      Node* children[2];
      Node() : size(0), parent(nullptr), children{nullptr,nullptr} {}
    };
    
    Node* const root;
    T xor_value;
};