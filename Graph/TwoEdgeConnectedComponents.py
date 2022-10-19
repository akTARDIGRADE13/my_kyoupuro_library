from typing import List
 
class TwoEdgeConnectedComponents:
    def __init__(self, n:int, G:List[List[int]]):
        self.n = n
        self.seen = [False]*n
        self.check_aps = [False]*n
        self.ord = [0]*n
        self.low = [0]*n
        self.G = G
        self.groups = []
        self.idx = [0]*n
        k = 0
        for i in range(n):
            if not self.seen[i]:
                self.dfs(i,-1,k)
        self.build()
    
    def build(self) -> None:
        self.seen = [False]*self.n
        cnt = 0
        for i in range(self.n):
            if self.seen[i]:
                continue
            q = [i]
            self.groups.append([])
            for j in q:
                if self.seen[j]:
                    continue
                self.groups[cnt].append(j)
                self.idx[j] = cnt
                self.seen[j] = True
                for k in self.G[j]:
                    if self.seen[k]:
                        continue
                    if self.is_bridges(j,k):
                        continue
                    q.append(k)
            cnt += 1

    def get_idx(self, x:int) -> int:
        return self.idx[x]
 
    def dfs(self, now:int, par:int, k:int) -> int:
        self.seen[now] = True
        self.ord[now] = k
        self.low[now] = k
        k += 1
        count = 0
        flag = True
        for i in self.G[now]:
            if i == par and flag:
                flag = False
                continue
            if self.seen[i]:
                self.low[now] = min(self.low[now],self.ord[i])
            else:
                count += 1
                k = self.dfs(i,now,k)
                self.low[now] = min(self.low[now],self.low[i])
                if par != -1 and self.ord[now] <= self.low[i]:
                    self.check_aps[now] = True
        if par == -1 and count >= 2:
            self.check_aps[now] = True
        return k
 
    def is_aps(self, x:int) -> bool:
        return self.check_aps[x]
    
    def is_bridges(self, x:int, y:int) -> bool:
        if self.ord[x] > self.ord[y]:
            x,y = y,x
        return self.ord[x] < self.low[y]