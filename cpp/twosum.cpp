#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> d;
        for (int i = 0;; ++i) {
            int x = nums[i];
            int y = target - x;
            if (d.find(y) != d.end()) {
                return {d[y], i};
            }
            d[x] = i;
        }
    }
};

int main() {
    vector<int> nums{2,7,11,15};
    auto result = Solution().twoSum(nums, 9);
    for (auto x : result) {
        printf("%d\n", x);
    }
    return 0;
}