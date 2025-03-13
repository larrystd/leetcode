from collections import deque
from typing import List

'''
给定一个由 0 和 1 组成的矩阵 mat ，请输出一个大小相同的矩阵，其中每一个格子是 mat 中对应位置元素到最近的 0 的距离。
两个相邻元素间的距离为 1 。
'''

'''
from collection import deque
deque double-ended queue, 双端队列
方法
append(x) 尾部添加元素
appendleft(x) 头部添加元素

pop() 删除尾部元素
popleft() 删除头部元素
'''


class Solution: 
    def updateMatrix(self, mat: List[List[int]]) -> List[List[int]]:
        m, n = len(mat), len(mat[0])
        ans = [[-1] * n for _ in range(m)]
        q = deque()
        for i, row in enumerate(mat):
            for j, x in enumerate(row):
                if x == 0:
                    ans[i][j] = 0
                    q.append((i, j))
        dirs = (-1, 0, 1, 0, -1)
        while q:
            i, j = q.popleft()
            for k in range(len(dirs)-1):
                x = i + dirs[k]
                y = j + dirs[k+1]
                if 0 <= x < m and 0 <= y < n and ans[x][y] == -1:
                    ans[x][y] = ans[i][j]+1
                    q.append((x, y))
        return ans
        
        
if __name__ == "__main__":
    mat = [[0,0,0],[0,1,0],[1,1,1]]
    print (Solution().updateMatrix(mat))