#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

uint64_t count_bytes(FILE* file) {
    uint64_t counter = 0;
    while (fgetc(file) != EOF) counter++;
    fseek(file, 0, SEEK_SET);
    return counter;
}

void overwrite(FILE* file, const char* fname, uint64_t iterations) {
    // mem: overwrite is responsible for the buffer it creates, that's it
    uint64_t bytes = count_bytes(file);
    printf("file: %s, %lu bytes found, overwirting it\n", fname, bytes);
    uint8_t* buffer = (uint8_t*) malloc(bytes);

    for (uint64_t overwrite_count=0; overwrite_count < iterations; overwrite_count++) {
        // write n times to the file
        for (uint64_t i=0; i < bytes; i++) {
            // fill in buffer with randoms bytes
            uint8_t num = (uint8_t)(rand() % 254);
            buffer[i] = num;
        }
        fwrite(&buffer, 1, bytes, file);
        fseek(file, 0, SEEK_SET);
    }

    free(buffer);
}

int main(const int argc, const char**argv) {
    srand(time(NULL));

    if (argc == 1) {
        printf("No files to shred\n");
        return EXIT_FAILURE;
    }

    for (uint64_t i = 1; i < argc; i++) {
        // iterate over given files
        printf("reading file : %s", argv[i]);
        FILE* write_file = fopen(argv[i], "rb+");
        if (write_file == NULL) {
            printf("Could not open file %s in write mode, continuing...", argv[i]);
        }
        overwrite(write_file, argv[i], 100);
        fclose(write_file);
    };
    return 0;
}
