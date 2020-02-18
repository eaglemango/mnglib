#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "integer.hpp"

const size_t VECTOR_SIZE = 4096 * 2;

template <class T>
void StupidBubbleSort(std::vector<T>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        for (size_t j = 0; j + 1 < v.size(); ++j) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
}

int main() {
    std::random_device device;
    std::mt19937 engine(device());
    std::uniform_int_distribution<int> uni(-1000, 1000);

    std::vector<Integer<int>> test_vector;

    for (size_t i = 0; i < VECTOR_SIZE; ++i) {
        test_vector.push_back(uni(engine));
    }

    std::vector<Integer<int>> test_vector_copy(test_vector);

    std::cout << "Generated vector size: " << VECTOR_SIZE << '\n' << '\n';

    Integer<int>::comp_count = 0;
    std::cout << "Testing StupidBubbleSort...\n";
    StupidBubbleSort(test_vector);
    std::cout << "StupidBubbleSort comparisons: " << Integer<int>::comp_count << '\n' << '\n';

    Integer<int>::comp_count = 0;
    std::cout << "Testing STL sort...\n";
    std::sort(test_vector_copy.begin(), test_vector_copy.end());
    std::cout << "STL sort comparisons: " << Integer<int>::comp_count << '\n';

    return 0;
}
