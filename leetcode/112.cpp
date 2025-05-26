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

    static constexpr int initLeaf(
        const TreeNode *treeNode,
        int sum,
        Stack<Task> &lifo
    ) noexcept {
        do {
            const auto left{treeNode->left}, right{treeNode->right};
            sum += treeNode->val;
            if (left && right)
                lifo.emplace(right, sum);
            if (left)
                treeNode = left;
            else
                treeNode = right;
        } while (treeNode);

        return sum;
    }

    static constexpr int nextLeaf(Stack<Task> &lifo) noexcept {
        const auto [treeNode, sum] = lifo.top();
        lifo.pop();

        return initLeaf(treeNode, sum, lifo);
    }

public:
    constexpr bool hasPathSum(
        const TreeNode * const root,
        const int targetSum
    ) const noexcept {
        if (!root)
            return false;

        Stack<Task> lifo{};
        auto sum{initLeaf(root, 0, lifo)};

        while (sum != targetSum && !empty(lifo))
            sum = nextLeaf(lifo);

        return sum == targetSum;
    }
};
