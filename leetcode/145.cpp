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
    constexpr vector<int> postorderTraversal(
        const TreeNode * const root
    ) const noexcept {
        vector<int> result{};
        if (!root)
            return result;

        Stack<const TreeNode *> lifo{};
        postorderInit(root, lifo);

        do {
            const auto treeNode{postorderNext(lifo)};
            result.push_back(treeNode->val);
        } while (!empty(lifo));

        return result;
    }
};
