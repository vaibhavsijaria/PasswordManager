#include "crypto.h"
#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 32
#define IV_SIZE 16

// Initialize CryptoUtils
CryptoUtils* CryptoUtils_init()
{
  CryptoUtils* crypto = malloc(sizeof(CryptoUtils));
  if(crypto == NULL)
  {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }

  crypto->mdctx = EVP_MD_CTX_new(); // Create a new/initialize Context
  if(crypto->mdctx == NULL)
  {
    perror("EVP_MD_CTX initialization failed");
    free(crypto);
    exit(EXIT_FAILURE);
  }

  return crypto;
}

// Clean up CryptoUtils
void CryptoUtils_cleanup(CryptoUtils* crypto)
{
  if(crypto)
  {
    EVP_MD_CTX_free(crypto->mdctx); // Free the Context
    free(crypto);
  }
}

// Hash data using SHA256 with key
Hash CryptoUtils_hashData(EVP_MD_CTX* mdctx, const char* data, const char* key)
{
  EVP_MD_CTX_reset(mdctx); // Reset the Context for re-use

  const EVP_MD* md = EVP_sha256(); // Use SHA256 algorithm
  Hash hash = malloc(EVP_MD_size(md));
  if(hash == NULL)
  {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }

  // Compute the hash
  EVP_DigestInit_ex(mdctx, md, NULL); // Initialize the digest context `mdctx` with the hash
                                      // algorithm `md` (SHA256 in this case)
  EVP_DigestUpdate(
      mdctx, data,
      strlen(data)); // Update the digest context `mdctx` with the data to be hashed (`data`)
  EVP_DigestUpdate(
      mdctx, key,
      strlen(key)); // Update the digest context `mdctx` with the key used for hashing (`key`)
  EVP_DigestFinal_ex(mdctx, hash,
                     NULL); // Finalize the digest computation in the context `mdctx` and store the
                            // result in `hash`.`hash` should be large enough to hold the result,
                            // typically allocated using EVP_MD_size(md)

  return hash;
}

// Verify data with hash using key
int CryptoUtils_verifyData(EVP_MD_CTX* mdctx, const char* data, const Hash hash, const char* key)
{
  Hash computedHash = CryptoUtils_hashData(mdctx, data, key);
  int result = memcmp(computedHash, hash, EVP_MD_size(EVP_sha256())) == 0;
  free(computedHash);
  return result;
}

// Function to print hash value
void CryptoUtils_printHash(Hash hash)
{
  for(int i = 0; i < EVP_MD_size(EVP_sha256()); i++)
  {
    printf("%02x", hash[i]);
  }
}

char* bin_to_hex(Hash hash)
{
  char* hex = malloc(EVP_MD_size(EVP_sha256()) * 2);
  if(!hex)
    return NULL;

  for(size_t i = 0; i < EVP_MD_size(EVP_sha256()); i++)
  {
    sprintf(hex + i * 2, "%02x", hash[i]);
  }

  return hex;
}

Hash hex_to_bin(const char* hex)
{
  size_t len = strlen(hex);
  if(len % 2 != 0)
    return NULL; // Invalid input

  size_t bin_len = len / 2;
  Hash bin = malloc(bin_len);
  if(!bin)
    return NULL;

  for(size_t i = 0; i < bin_len; i++)
  {
    sscanf(hex + i * 2, "%02hhx", &bin[i]);
  }

  return bin;
}

void encrypt_password(const char* password, unsigned char* key, unsigned char* iv,
                      unsigned char* encrypted_password)
{
  EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
  int len;

  // RAND_bytes(key, KEY_SIZE); // Generate a random key
  // RAND_bytes(iv, IV_SIZE);   // Generate a random initialization vector
  key = hex_to_bin(key);
  iv = hex_to_bin(iv);
  EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
  EVP_EncryptUpdate(ctx, encrypted_password, &len, (unsigned char*)password, strlen(password));
  EVP_EncryptFinal_ex(ctx, encrypted_password + len, &len);

  free(key);
  free(iv);
  EVP_CIPHER_CTX_free(ctx);
}

void decrypt_password(unsigned char* encrypted_password, unsigned char* key, unsigned char* iv,
                      char* decrypted_password)
{
  EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
  int len;

  EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
  EVP_DecryptUpdate(ctx, (unsigned char*)decrypted_password, &len, encrypted_password,
                    strlen(encrypted_password));
  EVP_DecryptFinal_ex(ctx, (unsigned char*)(decrypted_password + len), &len);

  EVP_CIPHER_CTX_free(ctx);
}