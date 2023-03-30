# verified with:
# https://atcoder.jp/contests/abc293/submissions/40172310
# https://atcoder.jp/contests/abc242/submissions/40172393

from math import sqrt, ceil
class Mo:
    def __init__(self, n, q, a):
        self.n = n
        self.q = q
        self.arr = a
        self.data = [0]*q
        self.query = [0]*q
        self.ans = [None]*q
        self.width = ceil(sqrt(3)*n/sqrt(2*q))
    
    def add(self, i, l, r):
        self.data[i] = (l<<20)|r
        l //= self.width
        self.query[i] = (l<<40) + ((-r if l&1 else r)<<20) + i
    
    # 問題に合わせて書き換える--------------------------------------------------------------
    # 必要な変数を追加で定義してもよい
    def initProcess(self):
        pass
        
    def addR(self, i):
        pass
        
    def addL(self, i):
        pass
 
    def delR(self, i):
        pass
 
    def delL(self, i):
        pass
 
    def rec(self, i):
        pass
    # ----------------------------------------------------------------------------------
 
    def solve(self):
        self.query.sort()
 
        self.l,self.r = 0,0 
 
        self.initProcess()
        mask = (1<<20)-1
        for i in self.query:
            idx = i & mask
            l,r = divmod(self.data[idx], 1<<20)
            while (self.l > l):
                self.l -= 1
                self.addL(self.l)
            while (self.r < r):
                self.addR(self.r)
                self.r += 1
            while (self.l < l):
                self.delL(self.l)
                self.l += 1
            while (self.r > r):
                self.r -= 1
                self.delR(self.r)
            self.rec(idx)
        return self.ans