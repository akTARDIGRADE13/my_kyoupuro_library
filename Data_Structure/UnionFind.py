# verified with:
# https://judge.yosupo.jp/submission/103479

# αはアッカーマンの逆関数
class UnionFind:
    # コンストラクタ
    def __init__(self, n):
        self.n = n   # 頂点の個数
        self.parents = [-1]*n   # 負なら連結成分の大きさ、非負なら親
    
    # 頂点xと頂点yをmerge <ならしO(α(n))>
    def merge(self,x, y):
        x = self.root(x)
        y = self.root(y)
        if x == y:
            return
        if self.parents[x] > self.parents[y]:
            x,y = y,x
        self.parents[x] += self.parents[y]
        self.parents[y] = x
        
    # 頂点xと頂点yが連結か否かを判定 <ならしO(α(n))>
    def same(self,x, y):
        x = self.root(x)
        y = self.root(y)
        return x == y

    # 頂点xの親を返す <ならしO(α(n))>
    def root(self,x):
        if self.parents[x] < 0:
            return x
        else:
            self.parents[x] = self.root(self.parents[x])
            return self.parents[x]
    
    # 頂点xが属する連結成分の大きさを返す <ならしO(α(n))>
    def size(self,x):
        return -self.parents[self.root(x)]
        
    # 連結成分ごとにまとめて返す <O(n)>
    def groups(self):
        ret = [[] for i in range(self.n)]
        for i in range(self.n):
            ret[self.root(i)].append(i)
        return [i for i in ret if len(i)]