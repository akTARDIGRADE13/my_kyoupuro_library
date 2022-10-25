# verified with:
# https://judge.yosupo.jp/submission/109770
# https://atcoder.jp/contests/abc255/submissions/35950398

from typing import List

class cartesian_tree:
	def __init__(self, n:int, val:List[int]) -> None:
		self.par = [-1]*n
		self.L = [-1]*n
		self.R = [-1]*n
		path = []
		for idx,i in enumerate(val):
			ko = -1
			while path and i < val[path[-1]]:
				ko = path.pop()
			if ko != -1:
				self.par[ko] = idx
			if path:
				self.par[idx] = path[-1]
			path.append(idx)
		for i in range(n):
			if self.par[i] == -1:
				self.par[i] = i # ここは根の親の定義に依存
				continue
			if i < self.par[i]:
				self.L[self.par[i]] = i
			else:
				self.R[self.par[i]] = i