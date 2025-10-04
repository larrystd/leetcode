#include <bits/stdc++.h>
#include <cstdio>


void quickSort(std::vector<int>& nums, int left, int right)
{
    if (right <= left)
    {
        return;
    }
    int base = nums[left];
    int i = left, j = right;
    while (i < j)
    {
        while (i < j && nums[j] >= base)
        {
            j--;
        }
        nums[i] = nums[j];
        while (i < j && nums[i] <= base)
        {
            i++;
        }
        nums[j] = nums[i];
    }
    assert(i == j);
    nums[i] = base;

    quickSort(nums, left, i - 1);
    quickSort(nums, i + 1, right);
}

int main()
{
    std::vector<int> nums = {3, 6, 8, 10, 1, 2, 1};
    quickSort(nums, 0, nums.size() - 1);
    for (int num : nums)
    {
        printf("%d ", num);
    }
    printf("\n");
    return 0;
}