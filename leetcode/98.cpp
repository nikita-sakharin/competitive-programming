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

    template<class T>
    static constexpr auto minV{numeric_limits<T>::min()};

    template<class T>
    static constexpr auto maxV{numeric_limits<T>::max()};

public:
    constexpr bool isValidBST(const TreeNode * const root) const noexcept {
        Stack<tuple<const TreeNode *, int, int>> lifo{};
        lifo.emplace(root, minV<int>, maxV<int>);

        do {
            const auto [treeNode, left, right]{lifo.top()};
            lifo.pop();
            if (treeNode->val < left || treeNode->val > right)
                return false;
            if (treeNode->left) {
                if (treeNode->val == minV<int>)
                    return false;
                lifo.emplace(treeNode->left, left, treeNode->val - 1);
            }
            if (treeNode->right) {
                if (treeNode->val == maxV<int>)
                    return false;
                lifo.emplace(treeNode->right, treeNode->val + 1, right);
            }
        } while (!empty(lifo));

        return true;
    }
};
