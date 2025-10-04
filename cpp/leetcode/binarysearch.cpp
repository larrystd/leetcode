/*
给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
*/

#include <bits/stdc++.h>


int binarySearch(const std::vector<int>& nums, int target)
{
    int i = 0, j = nums.size() - 1;
    while(i <= j)
    {
        int mid = i + (j - i) / 2;
        if (nums[mid] == target)
        {
            return mid;
        }
        else if (nums[mid] < target)
        {
            i = mid + 1;
        }
        else
        {
            j = mid - 1;
        }
    }
    return -1;
}

int main()
{
    std::vector<int> nums = {-1,0,3,5,9,12};
    printf("%d\n", binarySearch(nums, -1));
    printf("%d\n", binarySearch(nums, 9));
    printf("%d\n", binarySearch(nums, 12));
    return 0;
}