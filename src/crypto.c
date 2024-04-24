#include<crypto.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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