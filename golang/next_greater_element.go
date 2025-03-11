package main

import "fmt"

/*
 * golang这个语言比较特殊
 * golang不提供deque数据结构,
 * golang 切片只提供append(a, x)追加接口, 删除末尾元素用s[:len(s)-1]
 *
 * golang range一个列表, 返回ids和value
 * golang map返回key，可以同时返回key是否存在。if v, ok := d[x]; ok {
 */

func nextGreaterElement(nums1 []int, nums2 []int) (ans []int) {
	stk := []int{}
	d := map[int]int{}
	for i := len(nums2) - 1; i >= 0; i-- {
		x := nums2[i]
		for len(stk) > 0 && stk[len(stk)-1] < x {
			stk = stk[:len(stk)-1]
		}
		if len(stk) > 0 {
			d[x] = stk[len(stk)-1]
		}
		stk = append(stk, x)
	}
	for _, x := range nums1 {
		if v, ok := d[x]; ok {
			ans = append(ans, v)
		} else {
			ans = append(ans, -1)
		}
	}
	return
}

func main() {
	nums1 := []int{4, 1, 2}
	nums2 := []int{1, 3, 4, 2}
	fmt.Println(nextGreaterElement(nums1, nums2))
}
