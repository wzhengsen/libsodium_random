#include "sodium_random.hpp"

#include <random>
#include <cassert>
#include <concepts>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

template <class T>
[[nodiscard]] T Rand(auto&& gen, T min, T max) {
    assert(min <= max);
    if constexpr (std::is_integral<T>::value) {
        return std::uniform_int_distribution<T>(min, max)(gen);
    }
    else {
        return std::uniform_real_distribution<T>(min, max)(gen);
    }
}

static void WriteFileRNG(std::string_view file) {
    if (auto f = std::ofstream(file.data())) {
        std::string s = "";
        s.reserve(30'000'000);

        auto g = Sodium::RandomGenerator();
        for (uint64_t i = 0; i < 3'000'000; ++i) {
            s += std::to_string(Rand(g, 0u, std::numeric_limits<uint32_t>::max()));
            if (i != 3'000'000 - 1) {
                s += ',';
            }
        }

        f << s;
    }
}

int main() {
    std::cout << "-- Start benchmarking --" << std::endl;

    constexpr uint64_t TryTimes = 100'000'000;
    auto RandomGenerator        = Sodium::RandomGenerator();
    const auto minRange         = Rand(RandomGenerator, 1u, 50u);
    const auto maxRange         = Rand(RandomGenerator, minRange + 10u, minRange + 20u);

    auto times = std::vector<uint64_t>(maxRange - minRange + 1u);
    for (uint64_t i = 0; i < TryTimes; ++i) {
        const auto rand = Rand(RandomGenerator, minRange, maxRange);
        assert(rand >= minRange && rand <= maxRange);

        const auto idx = rand - minRange;
        ++times[idx];
    }

    std::cout << "minRange = " << minRange << std::endl;
    std::cout << "maxRange = " << maxRange << std::endl;
    std::cout << "Standard expectation = " << std::fixed << std::setprecision(4) << 1. / (maxRange - minRange + 1) * TryTimes << std::endl;
    std::cout << "Standard probability = " << 1. / (maxRange - minRange + 1) * 100. << "%" << std::endl;
    std::cout << std::endl;

    for (size_t i = 0; i < times.size(); ++i) {
        const auto probability = double(times[i]) / TryTimes * 100.;
        std::cout << i + minRange << " -> " << times[i] << " times," << std::setprecision(4) << probability << "% probability." << std::endl;
    }

    std::cout << "-- End benchmarking --" << std::endl;

    std::cout << "-- Start rng file --" << std::endl;
    WriteFileRNG("rng1.csv");
    WriteFileRNG("rng2.csv");
    WriteFileRNG("rng3.csv");
    std::cout << "-- End rng file --" << std::endl;

    return 0;
}
