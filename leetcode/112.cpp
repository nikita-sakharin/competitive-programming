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

    static constexpr int initLeaf(
        const TreeNode *treeNode,
        int sum,
        Stack<pair<const TreeNode *, int>> &lifo
    ) noexcept {
        do {
            sum += treeNode->val;
            if (treeNode->left && treeNode->right)
                lifo.emplace(treeNode, sum);
            if (treeNode->left)
                treeNode = treeNode->left;
            else
                treeNode = treeNode->right;
        } while (treeNode);

        return sum;
    }

    static constexpr int nextLeaf(
        Stack<pair<const TreeNode *, int>> &lifo
    ) noexcept {
        const auto [treeNode, sum] = lifo.top();
        lifo.pop();

        return initLeaf(treeNode->right, sum, lifo);
    }

public:
    constexpr bool hasPathSum(
        const TreeNode * const root,
        const int targetSum
    ) const noexcept {
        if (!root)
            return false;

        Stack<pair<const TreeNode *, int>> lifo{};
        auto sum{initLeaf(root, 0, lifo)};

        while (sum != targetSum && !empty(lifo))
            sum = nextLeaf(lifo);

        return sum == targetSum;
    }
};
