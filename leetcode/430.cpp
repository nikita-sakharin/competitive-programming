/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/
class Solution final {
private:
    template<class T>
    using Stack = stack<T, vector<T>>;

public:
    constexpr Node *flatten(Node * const head) const noexcept {
        if (!head)
            return nullptr;

        Stack<Node *> lifo{};
        auto current{head};
        while (current->next || current->child || !empty(lifo)) {
            if (current->child) {
                if (current->next)
                    lifo.push(current->next);
                current->next = current->child;
                current->next->prev = current;
                current->child = nullptr;
            }
            if (!current->next) {
                current->next = lifo.top();
                current->next->prev = current;
                lifo.pop();
            }
            current = current->next;
        }

        return head;
    }
};
