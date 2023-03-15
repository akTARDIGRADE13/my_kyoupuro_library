# verified with:
# https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_1_B
# https://atcoder.jp/contests/abc087/submissions/39746989
# https://atcoder.jp/contests/abc280/submissions/39747056

from typing import TypeVar, Callable, List

T = TypeVar("T")
class Weighted_UnionFind:
    def __init__(self, _n:int, _fx:Callable[[T,T],T], _inv:Callable[[T],T], _ex:T) -> None:
        self.n = _n
        self.fx = _fx
        self.inv = _inv
        self.ex = _ex
        self.parents = [-1]*_n
        self.potential = [_ex]*_n

    def merge(self, x:int, y:int, w:T) -> bool:
        w += self.weight(x)
        w -= self.weight(y)
        x = self.root(x)
        y = self.root(y)
        if x == y:
            return self.diff(x,y) == w
        else:
            if self.parents[x] > self.parents[y]:
                x,y = y,x
                w = self.inv(w)
            self.parents[x] += self.parents[y]
            self.parents[y] = x
            self.potential[y] = w
            return True

    def same(self, x:int, y:int) -> bool:
        return self.root(x) == self.root(y)
    
    def root(self, x:int) -> int:
        if self.parents[x] < 0:
            return x
        else:
            r = self.root(self.parents[x])
            self.potential[x] = self.fx(self.potential[x],self.potential[self.parents[x]])
            self.parents[x] = r
            return self.parents[x]
    
    def size(self, x:int) -> int:
        return -self.parents[self.root(x)]

    def weight(self, x:int) -> T:
        self.root(x)
        return self.potential[x]
    
    def diff(self, x:int, y:int) -> T:
        return self.fx(self.weight(y),self.inv(self.weight(x)))
  
    def groups(self) -> List[List[int]]:
        ret = [[] for i in range(self.n)]
        for i in range(self.n):
            ret[self.root(i)].append(i)
        return [i for i in ret if len(i)]