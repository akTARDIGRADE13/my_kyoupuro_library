# 内部は1-indexだが、関数の引数は0-index
from tkinter.messagebox import NO

class BIT:
    # コンストラクタ
    def __init__(self, _n:int) -> None:
        self.n = _n+1
        self.vec = [0]*(_n+1)

    # 加算 <O(logn)>
    def add(self, i:int, x:int) -> None:
        i += 1
        while i < self.n:
            self.vec[i] += x
            i += i&(-i)

    # 累積和[0,i) <O(logn)>
    def sum(self, i:int) -> int:
        ret = 0
        while i > 0:
            ret += self.vec[i]
            i -= i&(-i)
        return ret

    # 区間和[l,r) <O(logn)>
    def query(self, l:int, r:int) -> int:
        return self.sum(r)-self.sum(l)

    # 累積和のlower_bound() <O(logn)>
    def binary_search(self, x:int) -> int:
        ret = 0
        r = 1
        while r < self.n:
            r = r << 1
        while r > 0:
            if ret+r < self.n and self.vec[ret+r] < x:
                x -= self.vec[ret+r]
                ret += r
            r = r >> 1
        return ret