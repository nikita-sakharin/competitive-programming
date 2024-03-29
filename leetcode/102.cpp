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
    inline vector<vector<int>> levelOrder(
        const TreeNode * const root
    ) const noexcept {
        vector<vector<int>> result{};
        queue<const TreeNode *> q{};
        if (root)
            q.emplace();
        q.push(root);
        do {
            const auto treeNode{q.front()};
            q.pop();
            if (treeNode) {
                result.back().push_back(treeNode->val);
                if (treeNode->left)
                    q.emplace(treeNode->left);
                if (treeNode->right)
                    q.emplace(treeNode->right);
            } else if (!q.empty()) {
                result.emplace_back();
                q.emplace();
            }
        } while (!q.empty());
        return result;
    }
};
