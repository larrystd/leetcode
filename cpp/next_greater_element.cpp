#include <bits/stdc++.h>

using namespace std;

/*
 * C++ stack, pop()出栈, top()返回栈顶元素, push(x) 入栈
 */
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> stk;
        unordered_map<int, int> d;
        reverse(nums2.begin(), nums2.end());
        for (int x : nums2) {
            while (!stk.empty() && stk.top() < x) {
                stk.pop();
            }
            if (!stk.empty()) {
                d[x] = stk.top();
            }
            stk.push(x);
        }
        vector<int> ans;
        for (int x : nums1) {
            ans.push_back(d.count(x) ? d[x] : -1);
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> nums1{4, 1, 2};
    vector<int> nums2{1, 3, 4, 2};
    auto ans = s.nextGreaterElement(nums1, nums2);
    for (int x : ans) {
        printf("%d\n", x);
    }
}