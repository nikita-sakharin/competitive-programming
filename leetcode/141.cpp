/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution final {
public:
    constexpr bool hasCycle(const ListNode *head) const noexcept {
        auto fast{head};
        while (fast && fast->next) {
            head = head->next;
            fast = fast->next->next;
            if (head == fast)
                return true;
        }
        return false;
    }
};
