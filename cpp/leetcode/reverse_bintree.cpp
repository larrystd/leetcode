#include <bits/stdc++.h>

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* buildTree(const std::vector<int>& nums, int index)
{
    if (index >= nums.size())
    {
        return nullptr;
    }
    if (nums[index] == -1)
    {
        return nullptr;
    }
    TreeNode* root = new TreeNode(nums[index]);
    root->left = buildTree(nums, 2 * index + 1);
    root->right = buildTree(nums, 2 * index + 2);
    return root;
}

void printTree(TreeNode* root)
{
    if (root == nullptr)
    {
        return;
    }
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty())
    {
        TreeNode* node = q.front();
        q.pop();
        if (node != nullptr)
        {
            printf("%d ", node->val);
            q.push(node->left);
            q.push(node->right);
        }
    }
    printf("\n");
}

TreeNode* reverseTree(TreeNode* root)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    reverseTree(root->left);
    reverseTree(root->right);
    std::swap(root->left, root->right);
    return root;
}

int main()
{
    std::vector<int> nums = {4, 2, 7, 1, 3, 6, 9};
    TreeNode* root = buildTree(nums, 0);
    printTree(root);
    TreeNode* reversedRoot = reverseTree(root);
    printTree(reversedRoot);
    return 0;
}