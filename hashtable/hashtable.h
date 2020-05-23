#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <cstdlib>
#include <string_view>
#include <vector>

size_t StringHash(const std::string_view& string, size_t key);

class Node {
public:
    Node();
    Node(const std::string_view& key, int value);

    Node* next_;
    std::string_view key_;
    int value_{};
};

class Hashtable {
public:
    explicit Hashtable(size_t initial_max_size);

    void Insert(const std::string_view& key, int value);
    void Remove(const std::string_view& key);
    bool Find(const std::string_view& key) const;
    int Get(const std::string_view& key) const;

    size_t GetCurrSize() const;
    size_t GetMaxSize() const;

private:
    void Grow();
    bool IsEqual(const std::string_view& lhs, const std::string_view& rhs) const;
    void Insert(Node* new_node);

    std::vector<Node*> main_chain_;

    size_t current_size_;
    size_t max_size_;
};

#endif //HASHTABLE_HASHTABLE_H
