from typing import List

class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        if len(nums) <= 1:
            return len(nums)
        left = 0
        right = 1
        current = nums[0]
        while 1:
            while right < len(nums):
                if nums[right] != current:
                    current = nums[right]
                    break
                right += 1
                
            if right == len(nums):
                break
            left += 1
            nums[left] = current
        return left + 1
        
if __name__ == "__main__":
    nums = [0,0,1,1,1,2,2,3,3,4]
    print (Solution().removeDuplicates(nums))