#include <cassert>
#include <cstdlib>
#include <vector>

static const size_t CONTAINER_BLOCK_SIZE = 512;
static const size_t ONE_BLOCK = 1;

template <typename T>
class Container {
    public:
        // Constructors
        Container();
        Container(size_t blocks_count);

        // Rule of Three
        ~Container();
        Container(const Container& other_container);
        Container& operator=(const Container& other_container);

        // Rule of Five
        Container(Container&& other_container) noexcept;
        Container& operator=(Container&& other_container) noexcept;

        // Data interaction
        T& operator[](size_t element_index);

        void Set(size_t element_index, const T& value);
        const T& Get(size_t element_index) const;

        void PushBack(const T& value);
        void PopBack();

        // Container information
        size_t Size() const;
        bool Empty() const;

    private:
        std::vector<T*> blocks;

        size_t elements_count;
        size_t last_block_offset;

        // Blocks manipulation
        void CreateBlock();
        void DeleteBlock(size_t block_index);
};

// Constuctors ================================================================
template <typename T>
Container<T>::Container() {
    elements_count = 0;
    last_block_offset = 0;
}

template <typename T>
Container<T>::Container(size_t blocks_count) {
    assert(blocks_count >= 0);

    for (size_t i = 0; i < blocks_count; ++i) {
        CreateBlock();
    }

    elements_count = 0;
    last_block_offset = 0;
}
// ============================================================================

// Rule of Three ==============================================================
template <typename T>
Container<T>::~Container() {
    for (size_t i = 0; i < blocks.size(); ++i) {
        if (blocks[i]) {
            delete blocks[i];
        }
    }
}

template <typename T>
Container<T>::Container(const Container<T>& other_container) {
    // TODO
}

template <typename T>
Container<T>& Container<T>::operator=(const Container<T>& other_container) {
    // TODO
}
// ============================================================================

// Rule of Five ===============================================================
template <typename T>
Container<T>::Container(Container<T>&& other_container) noexcept {
    // TODO
}

template <typename T>
Container<T>& Container<T>::operator=(Container<T>&& other_container) noexcept {
    // TODO
}
// ============================================================================

// Data interaction ===========================================================
template <typename T>
T& Container<T>::operator[](size_t element_index) {
    size_t block_index = element_index / CONTAINER_BLOCK_SIZE;
    size_t element_offset = element_index % CONTAINER_BLOCK_SIZE;

    assert(element_index < elements_count);

    return blocks[block_index][element_offset];
}

template <typename T>
void Container<T>::Set(size_t element_index, const T& value) {
    operator[](element_index) = value;
}

template <typename T>
const T& Container<T>::Get(size_t element_index) const {
    return operator[](element_index);
}

template <typename T>
void Container<T>::PushBack(const T& value) {
    assert(elements_count < CONTAINER_BLOCK_SIZE * blocks.size());

    size_t block_index = elements_count / CONTAINER_BLOCK_SIZE;

    blocks[block_index][last_block_offset] = value;
    last_block_offset = (last_block_offset + 1) % CONTAINER_BLOCK_SIZE;

    ++elements_count;

    if (block_index == blocks.size() - 1 && last_block_offset == 0) {
        CreateBlock();
    } 
}

template <typename T>
void Container<T>::PopBack() {
    assert(elements_count);

    size_t block_index = elements_count / CONTAINER_BLOCK_SIZE;

    last_block_offset = (last_block_offset + CONTAINER_BLOCK_SIZE - 1) % CONTAINER_BLOCK_SIZE;

    if (block_index == blocks.size() - 1 && last_block_offset == CONTAINER_BLOCK_SIZE - 1) {
        DeleteBlock(blocks.size() - 1);
    }

    --elements_count;
}
// ============================================================================

// Container information ======================================================
template <typename T>
size_t Container<T>::Size() const {
    return elements_count;
}

template <typename T>
bool Container<T>::Empty() const {
    return !Size();
}
// ============================================================================

// Blocks manipulation ========================================================
template <typename T>
void Container<T>::CreateBlock() {
    T* new_block = (T*)calloc(ONE_BLOCK, CONTAINER_BLOCK_SIZE);
    assert(new_block);

    blocks.push_back(new_block);
}

template <typename T>
void Container<T>::DeleteBlock(size_t block_index) {
    assert(block_index < blocks.size());

    if (block_index == blocks.size() - 1) {
        elements_count -= last_block_offset;
        last_block_offset = 0;

    } else {
        elements_count -= CONTAINER_BLOCK_SIZE;
    }

    delete blocks[block_index];
    blocks.erase(block_index);
}
// ============================================================================
