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

public:
    constexpr int findSecondMinimumValue(
        const TreeNode * const root
    ) const noexcept {
        auto result{minV<int>};
        Stack<const TreeNode *> lifo{};
        lifo.push(root);

        const auto rootValue{root->val};
        do {
            const auto treeNode{lifo.top()};
            lifo.pop();

            if (const auto value{treeNode->val}; value != rootValue)
                result = max(result, -value);
            else if (treeNode->left) {
                lifo.push(treeNode->left);
                lifo.push(treeNode->right);
            }
        } while (!empty(lifo));

        return result == minV<int> ? -1 : -result;
    }
};
