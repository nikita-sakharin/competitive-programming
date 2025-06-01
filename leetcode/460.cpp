class LFUCache final {
private:
    using uint = unsigned;

    class Node final {
    public:
        int key{0}, value{0};
        uint frequency{0};
    };

    using Bucket = list<Node>;
    using BucketIterator = Bucket::iterator;
    using UnorderedMapIterator = unordered_map<uint, Bucket>::iterator;

    unordered_map<uint, Bucket> frequencies{};
    unordered_map<int, BucketIterator> index{};
    const size_t capacity{0};
    uint minFrequency{0};

    constexpr Bucket &bucket(const UnorderedMapIterator iter) noexcept {
        auto &elements{iter->second};
        if (minFrequency == 1)
            return elements;

        if (size(elements) == 1 && !frequencies.contains(1)) {
            auto nodeFrequencies{frequencies.extract(iter)};
            nodeFrequencies.key() = 1;
            frequencies.insert(move(nodeFrequencies));
            return elements;
        }

        return frequencies[1];
    }

    constexpr int &get(const BucketIterator bucketIter) noexcept {
        auto &[unused, value, frequency]{*bucketIter};
        const auto iter{frequencies.find(frequency)};
        auto &elements{iter->second}, &newElements{frequencies[frequency + 1]};
        newElements.splice(cend(newElements), elements, bucketIter);
        if (empty(elements)) {
            frequencies.erase(iter);
            if (minFrequency == frequency)
                minFrequency = frequency + 1;
        }
        ++frequency;

        return value;
    }

public:
    constexpr LFUCache(const int capacity) noexcept : capacity(capacity) {}

    constexpr int get(const int key) noexcept {
        const auto iter{index.find(key)};
        if (iter == cend(index))
            return -1;

        return get(iter->second);
    }

    constexpr void put(const int key, const int value) noexcept {
        const auto iter{index.find(key)};
        if (iter != cend(index)) {
            get(iter->second) = value;
            return;
        }

        if (size(index) >= capacity) {
            const auto iter{frequencies.find(minFrequency)};
            auto &elements{iter->second}, &newElements{bucket(iter)};
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
