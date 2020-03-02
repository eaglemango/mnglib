#include <iostream>

#include "container.hpp"

int main() {
    Container<int> ints(1);

    for (int i = 0; i < 20; ++i) {
        ints.PushBack(i * i);
    }

    for (int i = ints.Size() - 1; i >= 0; --i) {
        if (i % 2 == 0) {
            int num = ints.Get(i);
            ints.Set(i, num * -1);
        }

        std::cout << ints[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}
