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
    static constexpr pair<ListNode *, size_t> listTailAndSize(
        ListNode *listNode
    ) noexcept {
        auto length{1UZ};
        while (listNode->next) {
            listNode = listNode->next;
            ++length;
        }
        return {listNode, length};
    }

    static constexpr ListNode *nthNode(ListNode *listNode, size_t n) noexcept {
        for (; n != 0; --n)
            listNode = listNode->next;
        return listNode;
    }

public:
    constexpr ListNode *rotateRight(ListNode *head, int k) const noexcept {
        if (!head)
            return nullptr;

        auto [tail, length]{listTailAndSize(head)};
        k %= int(length);
        if (k != 0) {
            tail->next = head;
            tail = nthNode(head, length - size_t(k) - 1);
            head = tail->next;
            tail->next = nullptr;
        }

        return head;
    }
};
