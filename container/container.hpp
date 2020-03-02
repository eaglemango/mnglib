#include <vector>

static const size_t CONTAINER_BLOCK_SIZE = 512;

template <typename T>
class Container {
    public:
        // Constructors
        Container();

        // Rule of Three
        ~Container();
        Container(const Container& other_container);
        Container& operator=(const Container& other_container);

        // Rule of Five
        Container(Container&& other_container) noexcept;
        Container& operator=(Container&& other_container) noexcept;

        // Data interaction
        T& operator[](size_t index);

        void Set(size_t index, const T& value);
        const T& Get(size_t index) const;

        // Container information
        size_t Size() const;
        bool Empty() const;

    private:
        std::vector<T*> blocks;

        size_t last_block_offset;

        // Blocks manipulation
        void CreateBlock(size_t index);
        void DeleteBlock(size_t index);
};

// Constuctors ================================================================
template <typename T>
Container<T>::Container() {

}
// ============================================================================

// Rule of Three ==============================================================
template <typename T>
Container<T>::~Container() {

}

template <typename T>
Container<T>::Container(const Container<T>& other_container) {

}

template <typename T>
Container<T>& Container<T>::operator=(const Container<T>& other_container) {

}
// ============================================================================

// Rule of Five ===============================================================
template <typename T>
Container<T>::Container(Container<T>&& other_container) noexcept {

}

template <typename T>
Container<T>& Container<T>::operator=(Container<T>&& other_container) noexcept {

}
// ============================================================================

// Data interaction ===========================================================
template <typename T>
T& Container<T>::operator[](size_t index) {

}

template <typename T>
void Container<T>::Set(size_t index, const T& value) {

}

template <typename T>
const T& Container<T>::Get(size_t index) const {

}
// ============================================================================

// Container information ======================================================
template <typename T>
size_t Container<T>::Size() const {

}

template <typename T>
bool Container<T>::Empty() const {

}
// ============================================================================


// Blocks manipulation ========================================================
template <typename T>
void Container<T>::CreateBlock(size_t index) {

}

template <typename T>
void Container<T>::DeleteBlock(size_t index) {

}
// ============================================================================
