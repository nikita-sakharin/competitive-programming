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
public:
    constexpr TreeNode *searchBST(
        TreeNode *root,
        const int val
    ) const noexcept {
        while (root != nullptr) {
            const auto compare{val <=> root->val};
            if (compare < 0)
                root = root->left;
            else if (compare > 0)
                root = root->right;
            else
                return root;
        }

        return nullptr;
    }
};
