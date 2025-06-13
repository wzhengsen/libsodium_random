#pragma once
#include <cstdint>

namespace Sodium {
    struct RandomGenerator {
        using result_type = uint32_t;

        static constexpr result_type min() { return 0; }
        static constexpr result_type max() { return 0xFFFFFFFF; }

        result_type operator()() noexcept;
    };
}