/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution final {
private:
    enum class Operation : int {
        AND = 3,
        OR = 2
    };

    template<class T>
    using Stack = stack<T, vector<T>>;

    static constexpr void process(const int value, Stack<bool> &eval) noexcept {
        using enum Operation;

        if (const bool casted(value); value == casted) {
            eval.push(casted);
            return;
        }

        const auto right{eval.top()};
        eval.pop();
        const auto left{eval.top()};
        eval.pop();

        switch (Operation{value}) {
            case AND:
                eval.push(left && right);
                break;
            case OR:
                eval.push(left || right);
                break;
            default:
                unreachable();
        }
    }

    static constexpr bool hasRightSibling(
        const TreeNode * const treeNode,
        const TreeNode * const parent
    ) noexcept {
        return treeNode == parent->left && parent->right;
    }

    static constexpr void postorderInit(
        const TreeNode *treeNode,
        Stack<const TreeNode *> &lifo
    ) noexcept {
        do {
            lifo.push(treeNode);
            if (treeNode->left)
                treeNode = treeNode->left;
            else
                treeNode = treeNode->right;
        } while (treeNode);
    }

    static constexpr const TreeNode *postorderNext(
        Stack<const TreeNode *> &lifo
    ) noexcept {
        const auto treeNode{lifo.top()};
        lifo.pop();
        if (!empty(lifo) && hasRightSibling(treeNode, lifo.top()))
            postorderInit(lifo.top()->right, lifo);

        return treeNode;
    }

public:
    constexpr bool evaluateTree(const TreeNode * const root) const noexcept {
        Stack<const TreeNode *> lifo{};
        Stack<bool> eval{};
        postorderInit(root, lifo);

        do {
            const auto treeNode{postorderNext(lifo)};
            const auto value{treeNode->val};
            process(value, eval);
        } while (!empty(lifo));

        return eval.top();
    }
};
