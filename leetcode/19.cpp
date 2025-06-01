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
    static constexpr ListNode *nthNode(ListNode *listNode, size_t n) noexcept {
        for (; n != 0; --n)
            listNode = listNode->next;
        return listNode;
    }

public:
    constexpr ListNode *removeNthFromEnd(
        ListNode * const head,
        int n
    ) const noexcept {
        auto nthPrev{head}, current{nthNode(head, size_t(n))};
        if (!current)
            return head->next;

        while (current->next) {
            current = current->next;
            nthPrev = nthPrev->next;
        }
        nthPrev->next = nthPrev->next->next;

        return head;
    }
};
