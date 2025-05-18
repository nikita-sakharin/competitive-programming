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
    static constexpr bool isSymmetric(const TreeNode * const root) noexcept {
        using Task = pair<const TreeNode *, const TreeNode *>;

        if (!root->left && !root->right)
            return true;

        Container<Task> container{};
        const Accessor<Container<Task>> accessor{};
        container.emplace(root->left, root->right);

        do {
            const auto [left, right]{accessor(container)};
            container.pop();
            if (bool(left) != bool(right) || left->val != right->val)
                return false;
            if (left->left || right->right)
                container.emplace(left->left, right->right);
            if (left->right || right->left)
                container.emplace(left->right, right->left);
        } while (!empty(container));

        return true;
    }

    static constexpr bool isSymmetricBFS(const TreeNode * const root) noexcept {
        return isSymmetric<queue, Front>(root);
    }

    template<class T>
    using Stack = stack<T, vector<T>>;

    static constexpr bool isSymmetricDFS(const TreeNode * const root) noexcept {
        return isSymmetric<Stack, Top>(root);
    }

public:
    constexpr bool isSymmetric(const TreeNode * const root) const noexcept {
        return isSymmetricDFS(root);
    }
};
