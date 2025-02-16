package main

import "fmt"

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
	//fmt.Println(max(i))
	//fmt.Println(max(j, k))
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
