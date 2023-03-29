# verified with:
# https://atcoder.jp/contests/code-thanks-festival-2017-open/submissions/40153654
# https://atcoder.jp/contests/agc002/submissions/40153678

from typing import TypeVar, List
from bisect import bisect
 
T = TypeVar("T")
class PartialPersistentArray:
    def __init__(self, arr:List[T], t:int = 0) -> None:
        self.array = [[i] for i in arr]
        self.times = [[0] for _ in arr]
 
    def size(self) -> int:
        return len(self.array)
    
    def exist(self, idx:int, t:int) -> bool:
        if idx >= self.size():
            return False
        return self.times[idx][0] <= t
    
    def add(self, val:T, t:int) -> None:
        self.array.append([])
        self.array[-1].append(val)
        self.times.append([])
        self.times[-1].append(t)
 
    def update(self, val:T, idx:int, t:int) -> None:
        self.array[idx].append(val)
        self.times[idx].append(t)
 
    def get(self, idx:int, t:int) -> T:
        if self.times[idx][-1] <= t:
            return self.array[idx][-1]
        return self.array[idx][bisect(self.times[idx],t)-1]