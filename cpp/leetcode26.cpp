#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 1) {
		    return nums.size();
	    }
        int left = 0, right = 1;
        int current = nums[0];

        while(1) {
            for (; right < nums.size(); right++) {
                if (nums[right] != current) {
                    current = nums[right];
                    break;
                }
		    }
            if (right == nums.size()) {
                break;
            }
            left ++;
            nums[left] = current;
        }
        return left + 1;
    }
};

int main() {
    vector<int> nums{0,0,1,1,1,2,2,3,3,4};
    printf ("%d\n", Solution().removeDuplicates(nums));
    return 0;
}

