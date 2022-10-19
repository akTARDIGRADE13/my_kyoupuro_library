# 内部は1-indexだが、関数の引数は0-index
from typing import TypeVar, Callable
T = TypeVar("T")
class BIT:
    # コンストラクタ
    def __init__(self, _n, _fx: Callable[[T, T], T], _rev: Callable[[T], T], _ex):
        self.n = _n+1
        self.fx = _fx   # 二項演算
        self.rev = _rev   # 逆元
        self.ex = _ex   # 単位元
        self.vec = [_ex]*(_n+1)
 
    # 加算 <O(logn)>
    def add(self,i,x):
        i += 1
        while i < self.n:
            self.vec[i] = self.fx(self.vec[i],x)
            i += i&(-i)
 
    # 累積和[0,i) <O(logn)>
    def sum(self,i):
        ret = self.ex
        while i > 0:
            ret = self.fx(ret,self.vec[i])
            i -= i&(-i)
        return ret
 
    # 区間和[l,r) <O(logn)>
    def query(self,l,r):
        return self.fx(self.sum(r),self.rev(self.sum(l)))
 
    # 累積和のlower_bound() <O(logn)>
    def binary_search(self,x):
        ret = 0
        r = 1
        while r < self.n:
            r = r << 1
        while r > 0:
            if ret+r < self.n and self.vec[ret+r] < x:
                x = self.fx(x,self.rev(self.vec[ret+r]))
                ret += r
            r = r >> 1
        return ret