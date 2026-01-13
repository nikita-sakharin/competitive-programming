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
    constexpr ListNode *detectCycle(ListNode * const head) const noexcept {
        auto slow{head}, match{head};
        while (match && match->next) {
            slow = slow->next;
            match = match->next->next;
            if (slow == match)
                break;
        }

        if (!match || !match->next)
            return nullptr;

        slow = head;
        while (slow != match) {
            slow = slow->next;
            match = match->next;
        }

        return match;
    }
};
