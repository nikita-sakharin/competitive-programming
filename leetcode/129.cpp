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
        Stack<const TreeNode *> &lifo,
        int sum
    ) noexcept {
        do {
            lifo.push(treeNode);
            sum = sum * radix + treeNode->val;
            if (treeNode->left)
                treeNode = treeNode->left;
            else
                treeNode = treeNode->right;
        } while (treeNode);

        return sum;
    }

    static constexpr bool hasRightSibling(
        const TreeNode * const treeNode,
        const TreeNode * const parent
    ) noexcept {
        return treeNode == parent->left && parent->right;
    }

    static constexpr int nextLeaf(
        Stack<const TreeNode *> &lifo,
        int sum
    ) noexcept {
        const TreeNode *treeNode{};
        do {
            treeNode = lifo.top();
            lifo.pop();
            sum /= radix;
        } while (!empty(lifo) && !hasRightSibling(treeNode, lifo.top()));

        if (!empty(lifo))
            sum = initLeaf(lifo.top()->right, lifo, sum);

        return sum;
    }

public:
    constexpr int sumNumbers(const TreeNode * const root) const noexcept {
        Stack<const TreeNode *> lifo{};
        auto sum{initLeaf(root, lifo, 0)}, result{sum};

        do {
            sum = nextLeaf(lifo, sum);
            result += sum;
        } while (!empty(lifo));

        return result;
    }
};
