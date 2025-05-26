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
        unordered_map<const Node *, Node *> toNew{{listNode, result}};

        auto newListNode{result};
        while (listNode) {
            const auto next{listNode->next}, random{listNode->random};
            auto &newNext{toNew[next]}, &newRandom{toNew[random]};

            if (next) {
                if (!newNext)
                    newNext = new Node{next->val};
                newListNode->next = newNext;
            }
            if (random) {
                if (!newRandom)
                    newRandom = new Node{random->val};
                newListNode->random = newRandom;
            }

            listNode = next;
            newListNode = newListNode->next;
        }

        return result;
    }
};
