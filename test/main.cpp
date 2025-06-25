#include "sodium_random.hpp"

#include <random>
#include <cassert>
#include <concepts>
#include <iostream>
#include <iomanip>

auto RandomGenerator = Sodium::RandomGenerator();

template <class T>
[[nodiscard]] T Rand(T min, T max)
{
    assert(min <= max);
    if constexpr (std::is_integral<T>::value)
    {
        return std::uniform_int_distribution<T>(min, max)(RandomGenerator);
    }
    else
    {
        return std::uniform_real_distribution<T>(min, max)(RandomGenerator);
    }
}

int main() {
    constexpr uint64_t TryTimes = 100'000'000;

    const auto minRange = Rand(1u, 50u);
    const auto maxRange = Rand(minRange + 10u, minRange + 20u);

    auto times = std::vector<uint64_t>(maxRange - minRange + 1u);
    for (uint64_t i = 0; i < TryTimes; ++i) {
        const auto rand = Rand(minRange, maxRange);
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

    return 0;
}
