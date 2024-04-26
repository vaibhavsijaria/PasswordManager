#ifndef CRYPTO_H
#define CRYPTO_H

#include <openssl/evp.h>

typedef unsigned char* Hash;

typedef struct
{
  EVP_MD_CTX* mdctx;
} CryptoUtils;

CryptoUtils* CryptoUtils_init();
void CryptoUtils_cleanup(CryptoUtils* crypto);
Hash hex_to_bin(const char* hex);
char* bin_to_hex(Hash hash);
Hash CryptoUtils_hashData(EVP_MD_CTX* mdctx, const char* data, const char* key);
int CryptoUtils_verifyData(EVP_MD_CTX* mdctx, const char* data, const Hash hash, const char* key);
void CryptoUtils_printHash(Hash hash);
void encrypt_password(const char* password, unsigned char* key, unsigned char* iv,
                      unsigned char* encrypted_password);
void decrypt_password(unsigned char* encrypted_password, unsigned char* key, unsigned char* iv,
                      char* decrypted_password);

#endif