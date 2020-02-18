#include <cstdlib>

template <typename IntType>
class Integer {
    public:
        // Constructors
        Integer();
        Integer(IntType other_integer);

        operator IntType();

        // Rule of Three
        ~Integer();
        Integer(const Integer& other_integer);
        Integer& operator=(const Integer& ohter_integer);

        // Rule of Five
        Integer(Integer&& other_integer) noexcept;
        Integer& operator=(Integer&& other_integer) noexcept;

        // Unary operators
        Integer operator+() const;
        Integer operator-() const;
        Integer& operator++();
        Integer& operator--();
        Integer operator++(int);
        Integer operator--(int);

        // Binary arithmetic operators
        template <typename IntType_>
        friend const Integer<IntType_> operator+(const Integer<IntType_>& lhs, const Integer<IntType_>& rhs);

        template <typename IntType_>
        friend const Integer<IntType_> operator-(const Integer<IntType_>& lhs, const Integer<IntType_>& rhs);

        template <typename IntType_>
        friend const Integer<IntType_> operator*(const Integer<IntType_>& lhs, const Integer<IntType_>& rhs);

        template <typename IntType_>
        friend const Integer<IntType_> operator/(const Integer<IntType_>& lhs, const Integer<IntType_>& rhs);

        // Binary comparison operators
        template <typename IntType_>
        friend bool operator==(const Integer<IntType_>& lhs, const Integer<IntType_>& rhs);

        template <typename IntType_>
        friend bool operator!=(const Integer<IntType_>& lhs, const Integer<IntType_>& rhs);

        template <typename IntType_>
        friend bool operator<(const Integer<IntType_>& lhs, const Integer<IntType_>& rhs);

        template <typename IntType_>
        friend bool operator>(const Integer<IntType_>& lhs, const Integer<IntType_>& rhs);

        template <typename IntType_>
        friend bool operator<=(const Integer<IntType_>& lhs, const Integer<IntType_>& rhs);

        template <typename IntType_>
        friend bool operator>=(const Integer<IntType_>& lhs, const Integer<IntType_>& rhs);

        static size_t comp_count;

    private:
        IntType integer;
};

// Constructors ===============================================================
template <typename IntType>
Integer<IntType>::Integer() {
    integer = 0;
}

template <typename IntType>
Integer<IntType>::Integer(IntType other_integer) {
    integer = other_integer;
}

template <typename IntType>
Integer<IntType>::operator IntType() {
    return IntType(integer);
}
// ============================================================================

// Rule of Three ==============================================================
template <typename IntType>
Integer<IntType>::~Integer() {

}

template <typename IntType>
Integer<IntType>::Integer(const Integer<IntType>& other_integer) {
    integer = other_integer.integer;
}

template <typename IntType>
Integer<IntType>& Integer<IntType>::operator=(const Integer<IntType>& ohter_integer) {
    if (&ohter_integer == this) {
        return *this;
    }

    integer = ohter_integer.integer;

    return *this;
}
// ============================================================================

// Rule of Five ===============================================================
template <typename IntType>
Integer<IntType>::Integer(Integer<IntType>&& other_integer) noexcept {
    integer = other_integer.integer;
}

template <typename IntType>
Integer<IntType>& Integer<IntType>::operator=(Integer<IntType>&& other_integer) noexcept {
    if (&other_integer == this) {
        return *this;
    }

    integer = other_integer.integer;

    return *this;
}
// ============================================================================

// Unary operators ============================================================
template <typename IntType>
Integer<IntType> Integer<IntType>::operator+() const {
    return Integer<IntType>(integer);
}

template <typename IntType>
Integer<IntType> Integer<IntType>::operator-() const {
    return Integer<IntType>(-integer);
}

template <typename IntType>
Integer<IntType>& Integer<IntType>::operator++() {
    ++integer;

    return this;
}

template <typename IntType>
Integer<IntType>& Integer<IntType>::operator--() {
    --integer;

    return this;
}

template <typename IntType>
Integer<IntType> Integer<IntType>::operator++(int) {
    IntType temp = integer;
    ++integer;

    return Integer<IntType>(temp);
}

template <typename IntType>
Integer<IntType> Integer<IntType>::operator--(int) {
    IntType temp = integer;
    --integer;

    return Integer<IntType>(temp);
}
// ============================================================================

// Binary arithmetic operators ================================================
template <typename IntType>
const Integer<IntType> operator+(const Integer<IntType>& lhs, const Integer<IntType>& rhs) {
    return Integer<IntType>(lhs.integer + rhs.integer);
}

template <typename IntType>
const Integer<IntType> operator-(const Integer<IntType>& lhs, const Integer<IntType>& rhs) {
    return Integer<IntType>(lhs.integer - rhs.integer);
}

template <typename IntType>
const Integer<IntType> operator*(const Integer<IntType>& lhs, const Integer<IntType>& rhs) {
    return Integer<IntType>(lhs.integer * rhs.integer);
}

template <typename IntType>
const Integer<IntType> operator/(const Integer<IntType>& lhs, const Integer<IntType>& rhs) {
    return Integer<IntType>(lhs.integer / rhs.integer);
}
// ============================================================================

// Binary comparison operators ================================================
template <typename IntType>
bool operator==(const Integer<IntType>& lhs, const Integer<IntType>& rhs) {
    ++Integer<IntType>::comp_count;
    return lhs.integer == rhs.integer;
}

template <typename IntType>
bool operator!=(const Integer<IntType>& lhs, const Integer<IntType>& rhs) {
    ++Integer<IntType>::comp_count;
    return lhs.integer != rhs.integer;
}
template <typename IntType>
bool operator<(const Integer<IntType>& lhs, const Integer<IntType>& rhs) {
    ++Integer<IntType>::comp_count;
    return lhs.integer < rhs.integer;
}
template <typename IntType>
bool operator>(const Integer<IntType>& lhs, const Integer<IntType>& rhs) {
    ++Integer<IntType>::comp_count;
    return lhs.integer > rhs.integer;
}
template <typename IntType>
bool operator<=(const Integer<IntType>& lhs, const Integer<IntType>& rhs) {
    ++Integer<IntType>::comp_count;
    return lhs.integer <= rhs.integer;
}
template <typename IntType>
bool operator>=(const Integer<IntType>& lhs, const Integer<IntType>& rhs) {
    ++Integer<IntType>::comp_count;
    return lhs.integer >= rhs.integer;
}
// ============================================================================

template<typename IntType>
size_t Integer<IntType>::comp_count;
