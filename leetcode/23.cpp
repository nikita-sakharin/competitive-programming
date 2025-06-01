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
    struct Compare final {
    public:
        constexpr bool operator()(
            const ListNode * const lhs,
            const ListNode * const rhs
        ) const noexcept {
            return lhs->val > rhs->val;
        }
    };

public:
    constexpr ListNode *mergeKLists(vector<ListNode *> &lists) const noexcept {
        const auto first{begin(lists)};
        lists.resize(partition(first, end(lists), identity{}) - first);

        const Compare compare{};
        make_heap(first, end(lists), compare);

        ListNode *result{}, **ptr{&result};
        while (!empty(lists)) {
            const auto last{end(lists)};
            pop_heap(first, last, compare);
            auto &back{lists.back()};
            *ptr = back;
            ptr = &back->next;
            back = back->next;
            if (back)
                push_heap(first, last, compare);
            else
                lists.pop_back();
        }

        return result;
    }
};
