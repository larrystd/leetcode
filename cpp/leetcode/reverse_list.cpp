#include <bits/stdc++.h>

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* buildList(const std::vector<int>& nums)
{
    if (nums.empty())
    {
        return nullptr;
    }
    ListNode* head = new ListNode(nums[0]);
    ListNode* current = head;
    for (size_t i = 1; i < nums.size(); i++)
    {
        current->next = new ListNode(nums[i]);
        current = current->next;
    }
    return head;
}

ListNode* reverseList(ListNode* head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    ListNode* prev = head;
    ListNode* current = head->next;
    ListNode* next = current->next;
    head->next = nullptr;
    while(next != nullptr)
    {
        current->next = prev;
        prev = current;
        current = next;
        next = next->next;
    }
    current->next = prev;
    return current;
}

int main()
{
    std::vector<int> nums = {1, 2, 3, 4, 5};
    ListNode* head = buildList(nums);
    head = reverseList(head);
    while (head != nullptr)
    {
        printf("%d ", head->val);
        fflush(stdout);
        head = head->next;
    }
    printf("\n");
}