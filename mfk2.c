#include "mfk.h" // You might need to create an mfk.h if you have more function declarations
#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/sha.h> // For SHAKE128 
#include <string.h>

char* shake128(const char* data) { // Using SHAKE128 with a 256-bit output
    static char hash[SHA256_DIGEST_LENGTH * 2 + 1];

    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_shake128();

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, data, strlen(data));
    EVP_DigestFinalXOF(mdctx, (unsigned char*)hash, SHA256_DIGEST_LENGTH); 
    EVP_MD_CTX_free(mdctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash[i * 2], "%02x", (unsigned int)hash[i]);
    }

    return hash;
}

char* check(const char* arg1, int arg2) {
    // Concatenate the integer arg2 to the input string arg1
    char result[256]; // Adjust the size accordingly
    snprintf(result, sizeof(result), "%s%d", arg1, arg2);

    // Allocate memory for the result string
    char* hashResult = shake128(result);

    return hashResult;
}
