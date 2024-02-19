// mfk.c
#include "mfk.h" // Assuming you have this header file for any custom definitions
#include <stdio.h>
#include <openssl/evp.h> // Only needed if you had other OpenSSL usage prior
#include <string.h>
#include <blake2.h> 

char* blake2(const char* data) {
    static char hash[BLAKE2B_OUTBYTES * 2 + 1]; // Size for Blake2b output
    int outlen = BLAKE2B_OUTBYTES;

    blake2b(hash, outlen, data, strlen(data), NULL, 0);

    for (int i = 0; i < outlen; i++) {
        sprintf(&hash[i * 2], "%02x", (unsigned int)hash[i]);
    }

    return hash;
}

char* check(const char* arg1, int arg2) {
    // Concatenate the integer arg2 to the input string arg1
    char result[256]; // Adjust the size accordingly
    snprintf(result, sizeof(result), "%s%d", arg1, arg2);

    // Allocate memory for the result string
    char* hashResult = blake2(result);

    return hashResult;
}
