# verified with:
# https://judge.yosupo.jp/submission/109994
# https://judge.yosupo.jp/submission/109997
# https://atcoder.jp/contests/abc254/submissions/35985460

from typing import TypeVar, Callable, List

T = TypeVar("T")
class segment_tree:
    def __init__(self, _n:int, _fx:Callable[[T,T],T], _ex) -> None:
        self.n = 1
        self.fx = _fx
        self.ex = _ex
        while self.n < _n:
            self.n *= 2
        self.val = [self.ex]*self.n*2
    
    def set_list(self, a:List[T]) -> None:
        for i in range(len(a)):
            self.val[i+self.n] = a[i]
        for i in range(self.n-1,-1,-1):
            self.val[i] = self.fx(self.val[i<<1], self.val[(i<<1)|1])
    
    def add(self, i:int, x:T) -> None:
        i += self.n
        self.val[i] = self.fx(self.val[i], x)
        i >>= 1
        while i:
            self.val[i] = self.fx(self.val[i<<1],self.val[(i<<1)|1])
            i >>= 1
        
    def update(self, i:int, x:T) -> None:
        i += self.n
        self.val[i] = x
        i >>= 1
        while i:
            self.val[i] = self.fx(self.val[i<<1],self.val[(i<<1)|1])
            i >>= 1
    
    def query(self, l:int, r:int) -> T:
        vl = self.ex
        vr = self.ex
        l += self.n
        r += self.n
        while l < r:
            if l&1:
                vl = self.fx(vl,self.val[l])
                l += 1
            if r&1:
                r -= 1
                vr = self.fx(self.val[r],vr)
            l >>= 1
            r >>= 1
        return self.fx(vl,vr)