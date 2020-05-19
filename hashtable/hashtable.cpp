#include "hashtable.h"

static const size_t DEFAULT_KEY = 1337;

size_t StringHash(const std::string_view& string, size_t key) {
    size_t hash = 0;

    for (const char& i : string) {
        hash *= key;
        hash += i;
    }

    return hash;
}

Node::Node() : next_(nullptr) {

}

Hashtable::Hashtable(size_t initial_max_size) : current_size_(0), max_size_(initial_max_size) {
    main_chain_.resize(max_size_);
}

void Hashtable::Insert(const std::string_view& data) {
    if (current_size_ == max_size_) {
        Grow();
    }

    size_t hash = StringHash(data, DEFAULT_KEY) % max_size_;

    if (main_chain_[hash] == nullptr) {
        main_chain_[hash] = new Node();
        main_chain_[hash]->data_ = data;
    } else {
        Node* curr_node = main_chain_[hash];
        while (curr_node->next_ != nullptr) {
            curr_node = curr_node->next_;
        }

        curr_node->next_ = new Node();
        curr_node->next_->data_ = data;
    }

    ++current_size_;
}

void Hashtable::Remove(const std::string_view& data) {
    size_t hash = StringHash(data, DEFAULT_KEY) % max_size_;

    Node* prev_node = nullptr;
    Node* curr_node = main_chain_[hash];
    while (curr_node != nullptr) {
        if (curr_node->data_ == data) {
            if (prev_node != nullptr) {
                prev_node->next_ = curr_node->next_;
            } else {
                main_chain_[hash] = curr_node->next_;
            }

            delete curr_node;
            --current_size_;

            return;
        }
        prev_node = curr_node;
        curr_node = curr_node->next_;
    }
}

bool Hashtable::Find(const std::string_view& data) const {
    size_t hash = StringHash(data, DEFAULT_KEY) % max_size_;

    Node* curr_node = main_chain_[hash];
    while (curr_node != nullptr) {
        if (curr_node->data_ == data) {
            return true;
        }
        curr_node = curr_node->next_;
    }

    return false;
}

size_t Hashtable::GetCurrSize() const {
    return current_size_;
}

size_t Hashtable::GetMaxSize() const {
    return max_size_;
}

void Hashtable::Grow() {
    max_size_ <<= 1u;

    std::vector<Node*> old_chain_ = main_chain_;

    main_chain_.clear();
    main_chain_.resize(max_size_);

    for (Node* curr_node : old_chain_) {
        while (curr_node != nullptr) {
            Insert(curr_node->data_);

            Node* old_node = curr_node;
            curr_node = curr_node->next_;

            delete old_node;
        }
    }
}
