#include "sodium_random.hpp"
#include "include/sodium.h"

namespace Sodium {
    RandomGenerator::result_type RandomGenerator::operator()() noexcept {
        return ::randombytes_random();
    }
}