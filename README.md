# What's sodium_random?
sodium_random is a C++ wrapper library based on the C libsodium library.

# What is the purpose of sodium_random?
C libsodium is an easy-to-use software library that provides a wide range of cryptographic operations including encryption, decryption, digital signatures, and secure password hashing. In sodium_random, its secure password hashing function is mainly used.

In order to maximise key security and random number security without seed management, the library provides a set of functions to generate unpredictable data, suitable for creating secret keys:

* On Windows systems, the RtlGenRandom() function is used.

* On OpenBSD and Bitrig, the arc4random() function is used.

* On recent FreeBSD and Linux kernels, the getrandom system call is used.

* On other Unices, the /dev/urandom device is used.

All of the above secure random number calls are wrapped in a C++ random number generator called Sodium::RandomGenerator.

# Usage
To use this random number generator in a more concise manner without introducing additional external risks, we can use the C++ standard random distribution to generate random numbers using this random number generator. The following is a typical common usage:

```c++
// The unpredictability of random numbers can be guaranteed without using random seeds.


template <class T>
[[nodiscard]] T Rand(auto&& g, T min, T max) {
    assert(min <= max);
    if constexpr (std::is_integral<T>::value) {
        return std::uniform_int_distribution<T>(min, max)(g);
    }
    else {
        return std::uniform_real_distribution<T>(min, max)(g);
    }
}

int main() {
    auto RandomGenerator = Sodium::RandomGenerator();

    std::cout << Rand(RandomGenerator, 1, 100) << std::endl;
    std::cout << Rand(RandomGenerator, 0.5f, 2.5f) << std::endl;

    return 0;
}
```