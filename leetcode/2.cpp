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
private:
    static constexpr auto radix{10};

public:
    constexpr ListNode *addTwoNumbers(
        ListNode *l1,
        ListNode *l2
    ) const noexcept {
        const auto result{l1}, reserve{l2};
        auto carry{false};
        while (l1) {
            if (l2) {
                l1->val += l2->val;
                l2 = l2->next;
            }
            l1->val += carry;
            if (l1->val >= radix) {
                l1->val -= radix;
                carry = true;
            } else
                carry = false;
            if (!l1->next && l2)
                swap(l1->next, l2);
            else if (!l1->next && carry) {
                reserve->val = 0;
                reserve->next = nullptr;
                l1->next = reserve;
            }
            l1 = l1->next;
        }
        return result;
    }
};
