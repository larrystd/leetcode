#include <bits/stdc++.h>

using namespace std;

/*
 * emplace()和push的区别
 * push传入一个value, push(value_type&& __x)
 * emplace 传入可以构造value的参数, emplace(_Args&&... __args)
 * 例如对, queue<pair<int, int>> q
 * q.push({1, 2});
 * q.emplace(1, 2);
 *
 * C++ queue, 头文件#include <queue>
 * 方法, empty(), push(x), pop()
 * q.front(), back() 返回头尾函数
*/

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> ans(m, vector<int>(n, -1));
        queue<pair<int, int>> q;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 0) {
                    ans[i][j] = 0;
                    q.emplace(i, j);
                }
            }
        }
        vector<int> dirs = {-1, 0, 1, 0, -1};
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i) {
                int x = p.first + dirs[i];
                int y = p.second + dirs[i + 1];
                if (x >= 0 && x < m && y >= 0 && y < n && ans[x][y] == -1) {
                    ans[x][y] = ans[p.first][p.second] + 1;
                    q.emplace(x, y);
                }
            }
        }
        return ans;
    }
};

int main() {
    vector<vector<int>> mat = {
        {0,0,0},
        {0,1,0},
        {1,1,1}
    };
    auto ans = Solution().updateMatrix(mat);
    for (auto row : ans) {
        for (int x : row) {
            printf ("%d ", x);
        }
        printf("\n");
    }
}