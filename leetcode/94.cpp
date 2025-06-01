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

    static constexpr void inorderInit(
        const TreeNode *treeNode,
        Stack<const TreeNode *> &lifo
    ) noexcept {
        while (treeNode) {
            lifo.push(treeNode);
            treeNode = treeNode->left;
        }
    }

    static constexpr const TreeNode *inorderNext(
        Stack<const TreeNode *> &lifo
    ) noexcept {
        const auto treeNode{lifo.top()};
        lifo.pop();
        inorderInit(treeNode->right, lifo);
        return treeNode;
    }

public:
    constexpr vector<int> inorderTraversal(
        const TreeNode * const root
    ) const noexcept {
        vector<int> result{};
        Stack<const TreeNode *> lifo{};
        inorderInit(root, lifo);

        while (!empty(lifo)) {
            const auto treeNode{inorderNext(lifo)};
            result.push_back(treeNode->val);
        };

        return result;
    }
};
