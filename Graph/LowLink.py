from typing import List
 
class LowLink:
    def __init__(self, n:int, G:List[List[int]]):
        self.seen = [False]*n
        self.check_aps = [False]*n
        self.ord = [0]*n
        self.low = [0]*n
        self.aps = []
        self.bridges = []
        self.G = G
        k = 0
        for i in range(n):
            if not self.seen[i]:
                self.dfs(i,-1,k)
        self.aps.sort()
        self.bridges.sort()
 
    def dfs(self, now:int, par:int, k:int) -> int:
        self.seen[now] = True
        self.ord[now] = k
        self.low[now] = k
        k += 1
        count = 0
        for i in self.G[now]:
            if i == par:
                continue
            if self.seen[i]:
                self.low[now] = min(self.low[now],self.ord[i])
            else:
                count += 1
                k = self.dfs(i,now,k)
                self.low[now] = min(self.low[now],self.low[i])
                if par != -1 and self.ord[now] <= self.low[i]:
                    self.check_aps[now] = True
                if self.ord[now] < self.low[i]:
                    self.bridges.append([min(now,i),max(now,i)])
        if par == -1 and count >= 2:
            self.check_aps[now] = True
        if self.check_aps[now]:
            self.aps.append(now)
        return k
 
    def is_aps(self, x:int) -> bool:
        return self.check_aps[x]
    
    def is_bridges(self, x:int, y:int) -> bool:
        if self.ord[x] > self.ord[y]:
            x,y = y,x
        return self.ord[x] < self.low[y]