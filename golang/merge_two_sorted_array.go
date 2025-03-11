package main

import "fmt"

/* golang 一大特点是, 包外的函数都是大小字母开头, 其他语言一般都是小写字母
 *
 *
 */

func merge(nums1 []int, m int, nums2 []int, n int) {
	if n == 0 {
		return
	}
	i := m + n - 1
	j := m - 1
	k := n - 1
	for ; i >= 0 && j >= 0 && k >= 0; i-- {
		if nums1[j] > nums2[k] {
			nums1[i] = nums1[j]
			j--
		} else {
			nums1[i] = nums2[k]
			k--
		}
	}
	//fmt.Println(math.Max(i))
	//fmt.Println(math.Max(j, k))
	for ; k >= 0; k-- {
		nums1[k] = nums2[k]
	}
}

func main() {
	nums1 := []int{0, 0}
	nums2 := []int{2, 3}
	merge(nums1, 0, nums2, 2)
	fmt.Println(nums1)
}
