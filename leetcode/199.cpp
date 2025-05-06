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
    constexpr vector<int> rightSideView(
        const TreeNode * const root
    ) const noexcept {
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
};
