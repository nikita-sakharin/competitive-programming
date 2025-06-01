class Solution final {
public:
    constexpr int findContentChildren(
        vector<int> &g,
        vector<int> &s
    ) const noexcept {
        sort(begin(g), end(g));
        sort(begin(s), end(s));

        const auto gEnd{cend(g)}, sEnd{cend(s)};
        auto gIter{cbegin(g)}, sIter{cbegin(s)};
        while (gIter != gEnd && sIter != sEnd) {
            if (*gIter <= *sIter)
                ++gIter;
            ++sIter;
        }
        return gIter - cbegin(g);
    }
};
