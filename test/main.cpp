#include "sodium_random.hpp"

#include <cassert>
#include <concepts>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

static void WriteFileRNG(std::string_view file) {
    if (auto f = std::ofstream(file.data())) {
        std::string s = "";
        s.reserve(30'000'000);

        auto g = Sodium::RandomGenerator();
        for (uint64_t i = 0; i < 3'000'000; ++i) {
            s += std::to_string(Rand(g, 0u, std::numeric_limits<uint32_t>::max()));
            if (i != 3'000'000 - 1) {
                if ((i + 1) % 1'000 != 0) {
                    s += ',';
                }
                else {
                    s += '\n';
                }
            }
        }

        f << s;
    }
}

int main() {
    std::cout << "-- Write rng1.csv file --" << std::endl;
    WriteFileRNG("rng1.csv");

    std::cout << "-- Write rng2.csv file --" << std::endl;
    WriteFileRNG("rng2.csv");

    std::cout << "-- Write rng3.csv file --" << std::endl;
    WriteFileRNG("rng3.csv");

    return 0;
}
