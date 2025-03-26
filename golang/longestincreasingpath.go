package main

import "fmt"

func LongestIncreasingPath(matrix [][]int) int {
	m := len(matrix)
	n := len(matrix[0])

	cache := make([][]int, m)
	for i := 0; i < m; i++ {
		cache[i] = make([]int, n)
	}

	var dfs func(i, j int) int

	dfs = func(i, j int) int {
		if cache[i][j] > 0 {
			return cache[i][j]
		}
		dirs := []int{-1, 0, 1, 0, -1}
		maxIncreasingPath := 1
		for k := 0; k < 4; k++ {
			x := i + dirs[k]
			y := j + dirs[k+1]
			if x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] > matrix[i][j] {
				maxIncreasingPath = dfs(x, y) + 1
			}
		}
		cache[i][j] = maxIncreasingPath
		return maxIncreasingPath
	}

	result := 0
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			result = max(result, dfs(i, j))
		}
	}
	return result
}

func main() {
	metrix := [][]int{
		{9, 9, 4},
		{6, 6, 8},
		{2, 1, 1},
	}
	fmt.Println(LongestIncreasingPath(metrix))
}
