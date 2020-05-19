#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <cstdlib>
#include <string_view>
#include <vector>

size_t StringHash(const std::string_view& string, size_t key);

class Node {
public:
    Node();

    Node* next_;
    std::string_view data_;
};

class Hashtable {
public:
    explicit Hashtable(size_t initial_max_size);

    void Insert(const std::string_view& data);
    void Remove(const std::string_view& data);
    bool Find(const std::string_view& data) const;

    size_t GetCurrSize() const;
    size_t GetMaxSize() const;

private:
    void Grow();

    std::vector<Node*> main_chain_;

    size_t current_size_;
    size_t max_size_;
};

#endif //HASHTABLE_HASHTABLE_H
