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

    enum class BinaryOperator : int {
        AND = 0,
        OR = 1
    };

    enum class UnaryOperator : int {
        NOT = 0
    };

    template<template<class> class Container = vector>
    class Visitor final {
    private:
        stack<bool, Container<bool>> operands{};

    public:
        constexpr void operator()(const BinaryOperator value) noexcept {
            using enum BinaryOperator;

            const auto second{operands.top()};
            operands.pop();
            const auto first{operands.top()};
            operands.pop();

            switch (value) {
                case AND:
                    operands.push(first && second);
                    break;

                case OR:
                    operands.push(first || second);
                    break;

                default:
                    unreachable();
            }
        }

        constexpr void operator()(const UnaryOperator value) noexcept {
            using enum UnaryOperator;

            const auto first{operands.top()};
            operands.pop();

            switch (value) {
                case NOT:
                    operands.push(!first);
                    break;

                default:
                    unreachable();
            }
        }

        constexpr void operator()(const bool value) noexcept {
            operands.push(value);
        }

        constexpr bool get() const noexcept {
            return operands.top();
        }
    };

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

    static constexpr variant<bool, UnaryOperator, BinaryOperator> toVariant(
        const int value
    ) noexcept {
        using enum BinaryOperator;

        if (const bool casted(value); value == casted)
            return casted;

        return value == 3 ? AND : OR;
    }

public:
    constexpr bool evaluateTree(const TreeNode * const root) const noexcept {
        Stack<const TreeNode *> lifo{};
        postorderInit(root, lifo);

        Visitor visitor{};
        do {
            const auto treeNode{postorderNext(lifo)};
            const auto value{treeNode->val};
            visit(visitor, toVariant(value));
        } while (!empty(lifo));

        return visitor.get();
    }
};
