#include <fstream>
#include <string>
#include <string_view>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <cstring>
#include <ctime>

#include "hashtable.h"

static const uint64_t TEST_ITERATIONS = 100;

uint64_t GetFileSize(const std::string& filename) {
    struct stat stat_buf{};
    int rc = stat(filename.c_str(), &stat_buf);
    return stat_buf.st_size;
}

int main() {
    Hashtable hashtable(2);

    uint64_t file_size = GetFileSize("../data/words.txt");

    std::fstream words;
    words.open("../data/words.txt");

    std::cout << file_size << std::endl;
    char *buffer = new char[file_size];
    words.read(buffer, file_size);

    std::vector<std::string_view> views;
    char *buffer_ptr = buffer;
    char *delimiter = strchr(buffer_ptr, '\n');
    while (delimiter != nullptr) {
        *delimiter = '\0';
        views.emplace_back(std::string_view(buffer_ptr));

        buffer_ptr = delimiter + 1;
        delimiter = strchr(buffer_ptr, '\n');
    }

    std::cout << "Words count: " << views.size() << '\n';

    std::cout << "Running unit tests...\n";
    for (size_t test_iteration = 0; test_iteration < 1; ++test_iteration) {
        std::cout << "Inserting words to hashtable...\n";
        for (size_t i = 0; i < views.size(); ++i) {
            hashtable.Insert(views[i], i);
        }
        std::cout << "Insertion complete!\n";

        std::cout << "Trying to find all words...\n";
        bool all_found = true;
        for (const auto &view : views) {
            all_found &= hashtable.Find(view);
        }
        if (all_found) {
            std::cout << "All found!\n";
        } else {
            std::cout << "Words missing!\n";
        }

        std::cout << "Checking values correctness...\n";
        bool all_correct = true;
        for (size_t i = 0; i < views.size(); ++i) {
            if (hashtable.Get(views[i]) != i) {
                all_correct = false;
            }
        }
        if (all_correct) {
            std::cout << "All correct!\n";
        } else {
            std::cout << "Values incorrect!\n";
        }

        std::cout << "Removing all keys...\n";
        for (auto &view : views) {
            hashtable.Remove(view);
        }
        if (hashtable.GetCurrSize() == 0) {
            std::cout << "All keys removed!\n";
        } else {
            std::cout << "Not all keys removed!\n";
        }
    }
    std::cout << "Unit tests done!\n\n";

    std::cout << "Running stress test...\n";
    for (size_t test_iteration = 0; test_iteration < TEST_ITERATIONS; ++test_iteration) {
        for (size_t i = 0; i < views.size(); ++i) {
            hashtable.Insert(views[i], i);
        }

        bool all_found = true;
        for (const auto &view : views) {
            all_found &= hashtable.Find(view);
        }
        if (all_found) {
        } else {
            std::cout << "Words missing!\n";
        }

        bool all_correct = true;
        for (size_t i = 0; i < views.size(); ++i) {
            if (hashtable.Get(views[i]) != i) {
                all_correct = false;
            }
        }
        if (all_correct) {
        } else {
            std::cout << "Values incorrect!\n";
        }

        for (auto &view : views) {
            hashtable.Remove(view);
        }
        if (hashtable.GetCurrSize() == 0) {
        } else {
            std::cout << "Not all keys removed!\n";
        }
    }
    std::cout << "Stress test done!\n";

    delete[] buffer;
    words.close();

    std::cout << "Total run time: " << 1.0 * clock() / CLOCKS_PER_SEC << std::endl;

    return 0;
}
