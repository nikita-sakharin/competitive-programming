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
    template<class Container>
    using Value = Container::value_type;

    template<class Container>
    struct Front final {
    public:
        constexpr const Value<Container> &operator()(
            const Container &container
        ) const noexcept {
            return container.front();
        }
    };

    template<class Container>
    struct Top final {
    public:
        constexpr const Value<Container> &operator()(
            const Container &container
        ) const noexcept {
            return container.top();
        }
    };

    template<template<class> class Container, template<class> class Accessor>
    static constexpr bool isSameTree(
        const TreeNode * const first,
        const TreeNode * const second
    ) noexcept {
        using Task = pair<const TreeNode *, const TreeNode *>;

        if (!first && !second)
            return true;

        Container<Task> container{};
        const Accessor<Container<Task>> accessor{};
        container.emplace(first, second);

        do {
            const auto [left, right]{accessor(container)};
            container.pop();
            if (bool(left) != bool(right) || left->val != right->val)
                return false;
            if (left->left || right->left)
                container.emplace(left->left, right->left);
            if (left->right || right->right)
                container.emplace(left->right, right->right);
        } while (!empty(container));

        return true;
    }

    static constexpr bool isSameTreeBFS(
        const TreeNode * const first,
        const TreeNode * const second
    ) noexcept {
        return isSameTree<queue, Front>(first, second);
    }

    template<class T>
    using Stack = stack<T, vector<T>>;

    static constexpr bool isSameTreeDFS(
        const TreeNode * const first,
        const TreeNode * const second
    ) noexcept {
        return isSameTree<Stack, Top>(first, second);
    }

public:
    constexpr bool isSameTree(
        const TreeNode * const first,
        const TreeNode * const second
    ) const noexcept {
        return isSameTreeDFS(first, second);
    }
};
