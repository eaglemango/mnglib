#include "hashtable.h"

#include <string_view>

static const size_t DEFAULT_KEY = 1337;

size_t StringHash(const std::string_view& string, size_t key) {
    __asm__ volatile (R"(
        xorq    %rax, %rax

        movq    8(%rdi), %rbx

        movq    (%rdi), %rcx
        addq    %rbx, %rcx

    .Label1:
        cmpq    %rbx, %rcx
        je .Label2
        imulq   %rsi, %rax

        movsbq  (%rbx), %rdx
        addq    %rdx, %rax

        incq    %rbx
        jmp .Label1

    .Label2:
        movq    %rbp, %rsp
    )");
}

Node::Node() : next_(nullptr), value_(0) {

}

Node::Node(const std::string_view& key, int value) : next_(nullptr), key_(key), value_(value) {

}

Hashtable::Hashtable(size_t initial_max_size) : current_size_(0), max_size_(initial_max_size) {
    main_chain_.resize(max_size_);
}

void Hashtable::Insert(const std::string_view& key, int value) {
    if (current_size_ == 2 * max_size_) {
        Grow();
    }

    size_t hash = StringHash(key, DEFAULT_KEY) % max_size_;

    if (main_chain_[hash] == nullptr) {
        main_chain_[hash] = new Node(key, value);
    } else {
        Node* curr_node = main_chain_[hash];
        while (curr_node->next_ != nullptr) {
            curr_node = curr_node->next_;
        }

        curr_node->next_ = new Node(key, value);
    }

    ++current_size_;
}

void Hashtable::Remove(const std::string_view& key) {
    size_t hash = StringHash(key, DEFAULT_KEY) % max_size_;

    Node* prev_node = nullptr;
    Node* curr_node = main_chain_[hash];
    while (curr_node != nullptr) {
        if (IsEqual(curr_node->key_, key)) {
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

bool Hashtable::Find(const std::string_view& key) const {
    size_t hash = StringHash(key, DEFAULT_KEY) % max_size_;

    for (Node* curr_node = main_chain_[hash]; curr_node != nullptr; curr_node = curr_node->next_) {
        if (IsEqual(curr_node->key_, key)) {
            return true;
        }
    }

    return false;
}

int Hashtable::Get(const std::string_view& key) const {
    size_t hash = StringHash(key, DEFAULT_KEY) % max_size_;

    for (Node* curr_node = main_chain_[hash]; curr_node != nullptr; curr_node = curr_node->next_) {
        if (IsEqual(curr_node->key_, key)) {
            return curr_node->value_;
        }
    }

    return -1;
}

size_t Hashtable::GetCurrSize() const {
    return current_size_;
}

size_t Hashtable::GetMaxSize() const {
    return max_size_;
}

void Hashtable::Insert(Node* new_node) {
    if (current_size_ == 2 * max_size_) {
        Grow();
    }

    size_t hash = StringHash(new_node->key_, DEFAULT_KEY) % max_size_;

    if (main_chain_[hash] == nullptr) {
        main_chain_[hash] = new_node;
    } else {
        Node* curr_node = main_chain_[hash];
        while (curr_node->next_ != nullptr) {
            curr_node = curr_node->next_;
        }

        curr_node->next_ = new_node;
    }

    ++current_size_;
}

void Hashtable::Grow() {
    current_size_ = 0;
    max_size_ <<= 1u;

    std::vector<Node*> old_chain_ = main_chain_;

    main_chain_.clear();
    main_chain_.resize(max_size_);

    for (Node* curr_node : old_chain_) {
        while (curr_node != nullptr) {
            Node* old_node = curr_node;
            curr_node = curr_node->next_;
            old_node->next_ = nullptr;

            Insert(old_node);
        }
    }
}

bool Hashtable::IsEqual(const std::string_view &lhs, const std::string_view &rhs) const {
    __asm__ volatile (R"(
        xorq    %rax, %rax

        movq    (%rdx), %rbx
        cmpq    %rbx, (%rsi)
        jne .Label5

        movq    8(%rdx), %rdi

        movq    %rbx, %rdx
        addq    %rdi, %rdx

        movq    8(%rsi), %rsi

    .Label3:
        movsbq  (%rdi), %rbx
        movsbq  (%rsi), %rcx

        cmpq    %rbx, %rcx
        jne .Label5

        incq    %rdi
        incq    %rsi

        cmpq    %rdi, %rdx
        jne .Label3

    .Label4:
        incq    %rax

    .Label5:
        movq    %rbp, %rsp
    )");
}
