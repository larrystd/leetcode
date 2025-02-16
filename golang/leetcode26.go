package main

import "fmt"

func removeDuplicates(nums []int) int {
	if len(nums) <= 1 {
		return len(nums)
	}
	left := 0
	right := 1
	current := nums[0]
	for {
		for ; right < len(nums); right++ {
			if nums[right] != current {
				current = nums[right]
				break
			}
		}
		if right == len(nums) {
			break
		}
		left++
		nums[left] = current
	}
	return left + 1
}
func main() {
	nums := []int{0}
	fmt.Println(removeDuplicates(nums))
}
