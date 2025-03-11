from typing import List

'''
nums[::-1], 从右向左遍历
list.pop(), 移除元素，默认是最后一个元素
list.append(x), 从右侧加入
dict.get(x, -1), 如果不存在key返回-1
'''
class Solution:
    def nextGreaterElement(self, nums1: List[int], nums2: List[int]) -> List[int]:
        stk = []  # 单调递减栈
        d = {}  # value是key的next greater element
        for x in nums2[::-1]:
            print (x)
            while stk and stk[-1] < x:
                stk.pop()
            if stk:
                d[x] = stk[-1]
            stk.append(x)    
        return [d.get(x, -1) for x in nums1]
    
if __name__ == "__main__":
    nums1 = [4,1,2]
    nums2 = [1,3,4,2]
    print (Solution().nextGreaterElement(nums1, nums2))