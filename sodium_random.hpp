#pragma once
#include <cstdint>
#include <random>
#include <cassert>

namespace Sodium {
struct RandomGenerator {
    using result_type = uint32_t;

    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return 0xFFFFFFFF; }

    result_type operator()() noexcept;
};

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
}  // namespace Sodium