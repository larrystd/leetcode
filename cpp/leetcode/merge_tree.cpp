#include <bits/stdc++.h>

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* copyTree(TreeNode* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    TreeNode* newNode = new TreeNode(node->val);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}

TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2)
{
    if (t1 == nullptr && t2 == nullptr)
    {
        return nullptr;
    }
    int newVal = 0;
    if (t1 == nullptr)
    {
        newVal = t2->val;
    }
    else if (t2 == nullptr)
    {
        newVal = t1->val;
    }
    else
    {
        newVal = t1->val + t2->val;
    }
    TreeNode* newNode = new TreeNode(newVal);
    newNode->left = mergeTrees(t1->left, t2->left);
    newNode->right = mergeTrees(t1->right, t2->right);
    return newNode;
}