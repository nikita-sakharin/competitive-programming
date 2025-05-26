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
    template<class T>
    using Stack = stack<T, vector<T>>;

    using Task = pair<const TreeNode *, int>;

    static constexpr auto radix{10};

    static constexpr int initLeaf(
        const TreeNode *treeNode,
        int number,
        Stack<Task> &lifo
    ) noexcept {
        do {
            const auto left{treeNode->left}, right{treeNode->right};
            number = number * radix + treeNode->val;
            if (left && right)
                lifo.emplace(right, number);
            if (left)
                treeNode = left;
            else
                treeNode = right;
        } while (treeNode);

        return number;
    }

    static constexpr int nextLeaf(Stack<Task> &lifo) noexcept {
        const auto [treeNode, number] = lifo.top();
        lifo.pop();

        return initLeaf(treeNode, number, lifo);
    }

public:
    constexpr int sumNumbers(const TreeNode * const root) const noexcept {
        Stack<Task> lifo{};
        auto result{initLeaf(root, 0, lifo)};

        while (!empty(lifo))
            result += nextLeaf(lifo);

        return result;
    }
};
