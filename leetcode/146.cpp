class LRUCache final {
private:
    class Mapped final {
    public:
        pair<const int, Mapped> *prev{}, *next{};
        int value{0};
    };

    unordered_map<int, Mapped> index{};
    pair<const int, Mapped> *head{}, *tail{};
    const size_t capacity{0};

    constexpr int &get(pair<const int, Mapped> &element) noexcept {
        auto &mapped{element.second};
        (mapped.prev ? mapped.prev->second.next : head) = mapped.next;
        (mapped.next ? mapped.next->second.prev : tail) = mapped.prev;

        mapped.prev = tail;
        mapped.next = nullptr;
        tail = (tail ? tail->second.next : head) = &element;

        return mapped.value;
    }

public:
    inline LRUCache(const int capacity) noexcept : capacity(capacity) {}

    inline int get(const int key) noexcept {
        const auto iter{index.find(key)};
        if (iter == cend(index))
            return -1;
        return get(*iter);
    }

    inline void put(const int key, const int value) noexcept {
        const auto iter{index.find(key)};
        if (iter != cend(index)) {
            get(*iter) = value;
            return;
        }

        if (size(index) >= capacity) {
            const auto iter{index.find(head->first)};
            auto node{index.extract(iter)};
            node.key() = key;
            index.insert(move(node));
            get(*iter) = value;
        } else {
            auto &element{*index.emplace(key, Mapped{tail, nullptr, value}).first};
            tail = (tail ? tail->second.next : head) = &element;
        }
    }
};
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
