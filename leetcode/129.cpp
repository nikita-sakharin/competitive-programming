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

    static constexpr auto radix{10};

    static constexpr int initLeaf(
        const TreeNode *treeNode,
        Stack<pair<const TreeNode *, int>> &lifo,
        int number
    ) noexcept {
        do {
            number = number * radix + treeNode->val;
            if (treeNode->left && treeNode->right)
                lifo.emplace(treeNode, number);
            if (treeNode->left)
                treeNode = treeNode->left;
            else
                treeNode = treeNode->right;
        } while (treeNode);

        return number;
    }

    static constexpr int nextLeaf(
        Stack<pair<const TreeNode *, int>> &lifo
    ) noexcept {
        auto [treeNode, number] = lifo.top();
        lifo.pop();
        number = initLeaf(treeNode->right, lifo, number);

        return number;
    }

public:
    constexpr int sumNumbers(const TreeNode * const root) const noexcept {
        Stack<pair<const TreeNode *, int>> lifo{};
        auto number{initLeaf(root, lifo, 0)}, result{number};

        while (!empty(lifo)) {
            number = nextLeaf(lifo);
            result += number;
        }

        return result;
    }
};
