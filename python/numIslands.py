from itertools import pairwise
from typing import List

'''
dirs = (-1, 0, 1, 0, -1)
for a, b in pairwise(dirs):
自动生成(-1,0), (0,1), (1,0), (0,-1), 即挨个成对, 一共len()-1个对

dfs 可以用原地数字标记已经遍历过的位置(不需要额外的visit数组)
'''

class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        def dfs(i, j):
            grid[i][j] = '0'  # 遍历到的标记成海洋
            # for a, b in pairwise(dirs):
            for k, a in enumerate(dirs[:-1]):
                b = dirs[k+1]
                x, y = i + a, j + b
                if 0 <= x < m and 0 <= y < n and grid[x][y] == '1':
                    dfs(x, y)

        ans = 0
        dirs = (-1, 0, 1, 0, -1)
        m, n = len(grid), len(grid[0])
        for i in range(m):
            for j in range(n):
                if grid[i][j] == '1':
                    dfs(i, j)
                    ans += 1
        return ans
    
if __name__ == "__main__":
    dirs = (-1, 0, 1, 0, -1)
    for a, b in pairwise(dirs):
        print (a, b)
    grid = [
        ["1","1","1","1","0"],
        ["1","1","0","1","0"],
        ["1","1","0","0","0"],
        ["0","0","0","0","0"]
    ]
    print (Solution().numIslands(grid))