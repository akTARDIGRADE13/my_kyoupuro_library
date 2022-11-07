# verified with:
# https://atcoder.jp/contests/abc253/submissions/36301427

# 内部は1-indexだが、関数の引数は0-index
class range_BIT:
    # コンストラクタ
    def __init__(self, _n:int) -> None:
        self.n = _n+2
        self.vec = [[0]*(_n+2) for i in range(2)]
 
    # 加算 <O(logn)>
    def add(self, l:int, r:int, x:int) -> None:
        l += 1
        r += 1
        i = l
        while i < self.n:
            self.vec[0][i] -= x*(l-1)
            self.vec[1][i] += x
            i += i&(-i)
        i = r
        while i < self.n:
            self.vec[0][i] += x*(r-1)
            self.vec[1][i] -= x
            i += i&(-i)
 
    # 累積和[0,i) <O(logn)>
    def sum(self, i:int) -> int:
        ret = 0
        k = i
        while i > 0:
            ret += self.vec[1][i]*k+self.vec[0][i]
            i -= i&(-i)
        return ret
 
    # 区間和[l,r) <O(logn)>
    def query(self, l:int, r:int) -> int:
        return self.sum(r)-self.sum(l)