#include <bits/stdc++.h>

void reduce(std::vector<int>* nums, int left, int mid, int right)
{
    std::vector<int> temp(right-left + 1);
    int i = left, j = mid+1, k = 0;
    for (; i <= mid && j <= right; k++)
    {
        if (nums->at(i) <= nums->at(j))
        {
            temp[k] = nums->at(i);
            i++;
        }
        else
        {
            temp[k] = nums->at(j);
            j++;
        }
    }
    while (i <= mid)
    {
        temp[k] = nums->at(i);
        i++;
        k++;
    }
    while (j <= right)
    {
        temp[k] = nums->at(j);
        j++;
        k++;
    }
    for (int i = left; i <= right; i++)
    {
        nums->at(i) = temp[i-left];
    }
}

void mergeSort(std::vector<int>* nums, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int mid = left + (right - left) / 2;

    mergeSort(nums, left, mid);
    mergeSort(nums, mid + 1, right);
    reduce(nums, left, mid, right);
}

int main()
{
    std::vector<int> nums = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    mergeSort(&nums, 0, nums.size() - 1);
    for (int num : nums)
    {
        printf("%d ", num);
    }
    printf("\n");
}