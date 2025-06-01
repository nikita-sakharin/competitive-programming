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
    static constexpr size_t listSize(const ListNode *listNode) noexcept {
        auto length{0UZ};
        while (listNode) {
            listNode = listNode->next;
            ++length;
        }
        return length;
    }

    static constexpr ListNode **merge(
        ListNode *first,
        ListNode * const middle,
        ListNode * const last,
        ListNode **ptr
    ) noexcept {
        auto second{middle};
        while (first != middle || second != last) {
            if (first == middle
                || (second != last && second->val < first->val)
            ) {
                *ptr = second;
                second = second->next;
            } else {
                *ptr = first;
                first = first->next;
            }
            ptr = &(*ptr)->next;
        }
        *ptr = last;
        return ptr;
    }

    static constexpr ListNode *nthNode(ListNode *listNode, size_t n) noexcept {
        for (; n != 0; --n)
            listNode = listNode->next;
        return listNode;
    }

public:
    constexpr ListNode *sortList(ListNode *head) const noexcept {
        const auto length{listSize(head)}, half{length >> 1};
        auto step{1UZ};
        while (step < length) {
            auto n{length};
            auto ptr{&head};
            while (n != 0) {
                const auto left{min(step, n)}, right{min(step, n - left)};
                const auto middle{nthNode(*ptr, left)},
                    last{nthNode(middle, right)};
                ptr = merge(*ptr, middle, last, ptr);
                n -= left + right;
            }
            step = step <= half ? step << 1 : length;
        }
        return head;
    }
};
