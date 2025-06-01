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
    constexpr ListNode *mergeTwoLists(
        ListNode *list1,
        ListNode *list2
    ) const noexcept {
        ListNode *result{}, **ptr{&result};
        while (list1 && list2) {
            if (list2->val < list1->val) {
                *ptr = list2;
                list2 = list2->next;
            } else {
                *ptr = list1;
                list1 = list1->next;
            }
            ptr = &(*ptr)->next;
        }
        if (list1)
            *ptr = list1;
        else if (list2)
            *ptr = list2;
        return result;
    }
};
