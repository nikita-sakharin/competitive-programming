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

public:
    constexpr bool isSameTree(
        const TreeNode * const first,
        const TreeNode * const second
    ) const noexcept {
        if (!first && !second)
            return true;

        Stack<pair<const TreeNode *, const TreeNode *>> lifo{};
        lifo.emplace(first, second);

        do {
            const auto [left, right]{lifo.top()};
            lifo.pop();
            if (bool(left) != bool(right) || left->val != right->val)
                return false;
            if (left->left || right->left)
                lifo.emplace(left->left, right->left);
            if (left->right || right->right)
                lifo.emplace(left->right, right->right);
        } while (!empty(lifo));

        return true;
    }
};
