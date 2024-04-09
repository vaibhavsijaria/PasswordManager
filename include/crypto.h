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
Hash CryptoUtils_hashData(EVP_MD_CTX* mdctx, const char* data, const char* key);
int CryptoUtils_verifyData(EVP_MD_CTX* mdctx, const char* data, const Hash hash, const char* key);
void CryptoUtils_printHash(Hash hash);

#endif