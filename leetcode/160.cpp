/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution final {
private:
    static constexpr size_t listSize(const ListNode *listNode) noexcept {
        auto length{0UZ};
        while (listNode) {
            listNode = listNode->next;
            ++length;
        }

        return length;
    }

    static constexpr ListNode *nthNode(ListNode *listNode, size_t n) noexcept {
        for (; n != 0; --n)
            listNode = listNode->next;

        return listNode;
    }

public:
    constexpr ListNode *getIntersectionNode(
        ListNode *aHead,
        ListNode *bHead
    ) const noexcept {
        const auto aSize{listSize(aHead)}, bSize{listSize(bHead)};
        if (aSize < bSize)
            bHead = nthNode(bHead, bSize - aSize);
        else if (bSize < aSize)
            aHead = nthNode(aHead, aSize - bSize);
        while (aHead != bHead) {
            aHead = aHead->next;
            bHead = bHead->next;
        }

        return aHead;
    }
};
