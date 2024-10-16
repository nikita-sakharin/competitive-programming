class LFUCache final {
private:
    using uint = unsigned;

    class Node final {
    public:
        int key{0}, value{0};
        uint frequency{0};
    };

    unordered_map<int, list<Node>::iterator> index{};
    unordered_map<uint, list<Node>> frequencies{};
    const size_t capacity{0};
    uint minFrequency{0};

    inline int &get(const list<Node>::iterator nodeIter) noexcept {
        auto &[unused, value, frequency]{*nodeIter};
        const auto iter{frequencies.find(frequency)};
        auto &elements{iter->second}, &newElements{frequencies[frequency + 1]};
        newElements.splice(cend(newElements), elements, nodeIter);
        if (empty(elements)) {
            frequencies.erase(iter);
            if (minFrequency == frequency)
                minFrequency = frequency + 1;
        }
        ++frequency;
        return value;
    }

public:
    inline LFUCache(const int capacity) noexcept : capacity(capacity) {}

    inline int get(const int key) noexcept {
        const auto iter{index.find(key)};
        if (iter == cend(index))
            return -1;
        return get(iter->second);
    }

    inline void put(const int key, const int value) noexcept {
        const auto iter{index.find(key)};
        if (iter != cend(index)) {
            get(iter->second) = value;
            return;
        }

        if (size(index) >= capacity) {
            const auto iter{frequencies.find(minFrequency)};
            auto &elements{iter->second},
                &newElements{minFrequency == 1 ? elements : frequencies[1]};
            auto node{index.extract(elements.front().key)};
            node.key() = key;
            index.insert(move(node));
            newElements.splice(cend(newElements), elements, cbegin(elements));
            newElements.back() = {key, value, 1};
            if (empty(elements))
                frequencies.erase(iter);
        } else {
            auto &elements{frequencies[1]};
            elements.emplace_back(key, value, 1);
            index.emplace(key, --end(elements));
        }
        minFrequency = 1;
    }
};
/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
