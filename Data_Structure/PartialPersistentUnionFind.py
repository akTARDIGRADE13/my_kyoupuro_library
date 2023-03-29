# verified with:
# https://atcoder.jp/contests/code-thanks-festival-2017-open/submissions/40153654
# https://atcoder.jp/contests/agc002/submissions/40153678

# PartialPersistentArrayのライブラリを要求
from typing import TypeVar, List
from bisect import bisect

class PartialPersistentUnionFind:
    # コンストラクタ
    def __init__(self, n):
        self.n = n   # 頂点の個数
        self.parents = PartialPersistentArray([-1]*n)   # 負なら連結成分の大きさ、非負なら親
        #self.cnt_uni = [n]   # 連結成分の個数
        #self.times = [0]
    
    def merge(self, x:int , y:int, t:int = 1<<30):
        x = self.root(x)
        y = self.root(y)
        if x == y:
            return
        sx = self.parents.get(x,t)
        sy = self.parents.get(y,t)
        if sx > sy:
            self.parents.update(sx+sy,y,t)
            self.parents.update(y,x,t)
        else:
            self.parents.update(sx+sy,x,t)
            self.parents.update(x,y,t)
        #self.cnt_uni.append(self.cnt_uni[-1]-1)
        #self.times.append(t)
        
    def same(self, x:int, y:int, t:int = 1<<30):
        x = self.root(x,t)
        y = self.root(y,t)
        return x == y
    
    #def count_groups(self, t:int = 1<<30):
    #    if self.cnt_uni[-1] <= t:
    #        return self.cnt_uni[-1]
    #    return self.cnt_uni[bisect(self.times,t)-1]
 
    def root(self, x:int, t:int = 1<<30):
        if self.parents.get(x,t) < 0:
            return x
        else:
            return self.root(self.parents.get(x,t),t)
    
    def size(self, x, t):
        return -self.parents.get(self.root(x,t),t)
        
    def groups(self):
        ret = [[] for i in range(self.n)]
        for i in range(self.n):
            ret[self.root(i)].append(i)
        return [i for i in ret if len(i)]