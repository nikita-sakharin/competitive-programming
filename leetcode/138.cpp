/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution final {
public:
    constexpr Node *copyRandomList(const Node *listNode) const noexcept {
        if (!listNode)
            return nullptr;

        const auto result{new Node{listNode->val}};
        unordered_map<const Node *, Node *> dict{{listNode, result}};

        auto newListNode{result};
        do {
            const auto next{listNode->next}, random{listNode->random};
            if (next) {
                auto &newNext{dict[next]};
                if (!newNext)
                    newNext = new Node{next->val};
                newListNode->next = newNext;
            }
            if (random) {
                auto &newRandom{dict[random]};
                if (!newRandom)
                    newRandom = new Node{random->val};
                newListNode->random = newRandom;
            }

            listNode = next;
            newListNode = newListNode->next;
        } while (listNode);

        return result;
    }
};
