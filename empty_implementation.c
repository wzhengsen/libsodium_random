
// 这些函数完全用不着，但又必须编译通过，给空实现在这。
int _crypto_pwhash_argon2_pick_best_implementation(void) { return 0; }
int _crypto_generichash_blake2b_pick_best_implementation(void) { return 0; }
int _crypto_onetimeauth_poly1305_pick_best_implementation(void) { return 0; }
int _crypto_scalarmult_curve25519_pick_best_implementation(void) { return 0; }
int _crypto_stream_chacha20_pick_best_implementation(void) { return 0; }
int _crypto_stream_salsa20_pick_best_implementation(void) { return 0; }
int _crypto_aead_aegis128l_pick_best_implementation(void) { return 0; }
int _crypto_aead_aegis256_pick_best_implementation(void) { return 0; }

int crypto_stream_chacha20_ietf(unsigned char *c, unsigned long long clen,
                                const unsigned char *n, const unsigned char *k) { return 0; }