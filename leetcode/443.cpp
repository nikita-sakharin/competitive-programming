class Solution final {
public:
    constexpr int compress(vector<char> &chars) const noexcept {
        const auto length{size(chars)};
        const auto ptrEnd{data(chars) + length};
        auto ptr{data(chars) + 1};
        auto cnt{1UZ};
        for (auto i{1UZ}; i < length; ++i) {
            if (chars[i - 1] != chars[i]) {
                if (cnt > 1)
                    ptr = to_chars(ptr, ptrEnd, cnt).ptr;
                cnt = 0;
                *ptr++ = chars[i];
            }
            ++cnt;
        }

        if (cnt > 1)
            ptr = to_chars(ptr, ptrEnd, cnt).ptr;
        chars.resize(size_t(ptr - data(chars)));

        return int(size(chars));
    }
};
