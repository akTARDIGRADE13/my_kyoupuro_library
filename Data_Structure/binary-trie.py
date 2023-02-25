# verified with:
# https://judge.yosupo.jp/submission/127733
# https://atcoder.jp/contests/arc033/submissions/39206137
# https://atcoder.jp/contests/typical-algorithm/submissions/39206121
# https://atcoder.jp/contests/abc253/submissions/39205795

class BinaryTrie:
    def __init__(self, MAX_LOG:int = 32) -> None:
        self.MAX_LOG = MAX_LOG
        self.root = 0
        self.xor_value = 0
        self.next = 1
        self.size = [0]
        self.parent = [-1]
        self.children= [-1,-1]
    
    def insert(self, x:int, cnt:int = 1) -> None:
        x ^= self.xor_value
        tmp = self.root
        self.size[tmp] += cnt
        for i in range(self.MAX_LOG-1,-1,-1):
            b = (x>>i)&1
            if self.children[(tmp<<1)|b] == -1:
                self.children[(tmp<<1)|b] = self.next
                self.size.append(0)
                self.parent.append(tmp)
                self.children.extend([-1,-1])
                self.next += 1
            tmp = self.children[(tmp<<1)|b]
            self.size[tmp] += cnt
    
    def erase(self, x:int, cnt:int = 1) -> None:
        x ^= self.xor_value
        tmp = self.root
        cnt = min(cnt,self.count(x))
        if not cnt:
            return
        self.size[tmp] -= cnt
        for i in range(self.MAX_LOG-1,-1,-1):
            b = (x>>i)&1
            tmp = self.children[(tmp<<1)|b]
            self.size[tmp] -= cnt
        for i in range(self.MAX_LOG):
            if self.size[tmp]:
                break
            p = self.parent[tmp]
            b = (x>>i)&1
            self.children[(p<<1)|b] = -1
            self.parent[tmp] = -1
            tmp = p
    
    def count(self, x:int) -> int:
        x ^= self.xor_value
        tmp = self.root
        for i in range(self.MAX_LOG-1,-1,-1):
            b = (x>>i)&1
            if (self.children[(tmp<<1)|b] == -1):
                return 0
            tmp = self.children[(tmp<<1)|b]
        return self.size[tmp]
    
    def kth_element(self, k:int) -> int:
        k += 1
        tmp = self.root
        ret = 0
        for i in range(self.MAX_LOG-1,-1,-1):
            b = (self.xor_value>>i)&1
            if (self.children[(tmp<<1)|b] == -1 or self.size[self.children[(tmp<<1)|b]] < k):
                if(self.children[(tmp<<1)|b] != -1):
                    k -= self.size[self.children[(tmp<<1)|b]]
                b ^= 1
            ret <<= 1
            ret |= b
            tmp = self.children[(tmp<<1)|b]
        return ret^self.xor_value
    
    def count_leq(self, x:int) -> int:
        tmp = self.root
        ret = 0
        for i in range(self.MAX_LOG-1,-1,-1):
            b = ((self.xor_value^x)>>i)&1
            t = (x>>i)&1
            if t and self.children[(tmp<<1)|(b^1)] != -1:
                ret += self.size[self.children[(tmp<<1)|(b^1)]]
            if self.children[(tmp<<1)|b] == -1:
                return ret
            tmp = self.children[(tmp<<1)|b]
        return ret+self.size[tmp]
    
    def count_geq(self, x:int) -> int:
        tmp = self.root
        ret = 0
        for i in range(self.MAX_LOG-1,-1,-1):
            b = ((self.xor_value^x)>>i)&1
            t = (x>>i)&1
            if not t and self.children[(tmp<<1)|(b^1)] != -1:
                ret += self.size[self.children[(tmp<<1)|(b^1)]]
            if self.children[(tmp<<1)|b] == -1:
                return ret
            tmp = self.children[(tmp<<1)|b]
        return ret+self.size[tmp]
    
    def xor_all(self, x:int) -> None:
        self.xor_value ^= x
        
    def len(self) -> int:
        return self.size[self.root]
    
    def max(self) -> int:
        return self.kth_element(self.len()-1)
 
    def min(self) -> int:
        return self.kth_element(0)