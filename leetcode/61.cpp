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
    static constexpr pair<ListNode *, size_t> tailElement(
        ListNode *listNode
    ) noexcept {
        size_t result{1};
        while (listNode->next) {
            listNode = listNode->next;
            ++result;
        }
        return {listNode, result};
    }

    static constexpr ListNode *nthElement(
        ListNode *listNode,
        size_t index
    ) noexcept {
        for (; index != 0; --index)
            listNode = listNode->next;
        return listNode;
    }

public:
    constexpr ListNode *rotateRight(ListNode *head, int k) const noexcept {
        if (!head)
            return nullptr;
        auto [tail, size] = tailElement(head);
        k %= size;
        if (k != 0) {
            tail->next = head;
            tail = nthElement(head, size - k - 1);
            head = tail->next;
            tail->next = nullptr;
        }
        return head;
    }
};
