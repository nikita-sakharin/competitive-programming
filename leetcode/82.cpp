/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution final {
public:
    constexpr ListNode *deleteDuplicates(ListNode *head) const noexcept {
        auto current{head}, *ptr{&head};
        while (current) {
            if (current->next && current->val == current->next->val) {
                do
                    current = current->next;
                while (current->next && current->val == current->next->val);
                *ptr = current->next;
            } else
                ptr = &current->next;
            current = current->next;
        }
        return head;
    }
};
