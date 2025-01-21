#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void encrypt_decrypt_file(const char *input_path, const char *output_path, const char *key);
void validate_file(FILE *file, const char *path);

int main() {
    char input_path[256], output_path[256], key[256];

    // Welcome message
    printf("Welcome to the File Encryption and Decryption System\n");

    // Get user input
    printf("Enter input file path: ");
    scanf("%255[^\n]%*c", input_path); // Accept spaces in file path

    printf("Enter output file path: ");
    scanf("%255[^\n]%*c", output_path); // Accept spaces in file path

    printf("Enter encryption/decryption key: ");
    scanf("%255s", key); // Read encryption key

    // Perform encryption or decryption
    encrypt_decrypt_file(input_path, output_path, key);

    return 0;
}

void encrypt_decrypt_file(const char *input_path, const char *output_path, const char *key) {
    // Open the input file in binary read mode
    FILE *input_file = fopen(input_path, "rb");
    validate_file(input_file, input_path);

    // Open the output file in binary write mode
    FILE *output_file = fopen(output_path, "wb");
    validate_file(output_file, output_path);

    size_t key_length = strlen(key);
    size_t i = 0;
    int byte;

    // Process each byte in the input file
    while ((byte = fgetc(input_file)) != EOF) {
        fputc(byte ^ key[i % key_length], output_file); // XOR encryption/decryption
        i++;
    }

    printf("Operation completed successfully. Encrypted/Decrypted file saved at '%s'\n", output_path);

    // Close files
    fclose(input_file);
    fclose(output_file);
}

void validate_file(FILE *file, const char *path) {
    if (file == NULL) {
        perror(path); // Print detailed error message
        exit(EXIT_FAILURE); // Exit program if file cannot be opened
    }
}
