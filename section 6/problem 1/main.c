#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <openssl/sha.h>


int main() {
    FILE *file = fopen("example.txt", "rb");
    if (!file) return 1;

    unsigned char data[1024];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;

    SHA256_Init(&ctx);

    size_t bytes;
    while ((bytes = fread(data, 1, 1024, file)) != 0)
        SHA256_Update(&ctx, data, bytes);

    SHA256_Final(hash, &ctx);

    fclose(file);

    printf("SHA256: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        printf("%02x", hash[i]);
    printf("\n");

    return 0;
}