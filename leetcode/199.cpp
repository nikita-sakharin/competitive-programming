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
    template<class T>
    using Stack = stack<T, vector<T>>;

    static constexpr vector<int> rightSideViewBFS(
        const TreeNode * const root
    ) noexcept {
        vector<int> result{};
        if (!root)
            return result;

        queue<const TreeNode *> fifo{};
        fifo.push(root);

        do {
            result.push_back(fifo.front()->val);
            auto length{size(fifo)};
            do {
                const auto treeNode{fifo.front()};
                fifo.pop();
                --length;
                if (treeNode->right)
                    fifo.push(treeNode->right);
                if (treeNode->left)
                    fifo.push(treeNode->left);
            } while (length != 0);
        } while (!empty(fifo));

        return result;
    }

    static constexpr vector<int> rightSideViewDFS(
        const TreeNode * const root
    ) noexcept {
        using Task = pair<const TreeNode *, size_t>;

        vector<int> result{};
        if (!root)
            return result;

        Stack<Task> lifo{};
        lifo.emplace(root, 0);

        do {
            const auto [treeNode, depth]{lifo.top()};
            lifo.pop();
            if (depth >= result.size())
                result.push_back(treeNode->val);
            else
                result[depth] = treeNode->val;
            if (treeNode->right)
                lifo.emplace(treeNode->right, depth + 1);
            if (treeNode->left)
                lifo.emplace(treeNode->left, depth + 1);
        } while (!empty(lifo));

        return result;
    }

public:
    constexpr vector<int> rightSideView(
        const TreeNode * const root
    ) const noexcept {
        return rightSideViewDFS(root);
    }
};
