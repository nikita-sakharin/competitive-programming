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

    static constexpr bool hasRightSibling(
        const TreeNode * const treeNode,
        const TreeNode * const parent
    ) noexcept {
        return parent->right && treeNode == parent->left;
    }

public:
    inline bool hasPathSum(
        const TreeNode *treeNode,
        int targetSum
    ) const noexcept {
        Stack<const TreeNode *> lifo{};
        while (treeNode) {
            lifo.push(treeNode);
            targetSum -= treeNode->val;
            if (treeNode->left)
                treeNode = treeNode->left;
            else
                treeNode = treeNode->right;
        }

        while (!empty(lifo)) {
            treeNode = lifo.top()->right;
            while (treeNode) {
                lifo.push(treeNode);
                targetSum -= treeNode->val;
                if (treeNode->left)
                    treeNode = treeNode->left;
                else
                    treeNode = treeNode->right;
            }

            if (targetSum == 0)
                return true;

            do {
                treeNode = lifo.top();
                targetSum += treeNode->val;
                lifo.pop();
            } while (!empty(lifo) && !hasRightSibling(treeNode, lifo.top()));
        }

        return false;
    }
};
