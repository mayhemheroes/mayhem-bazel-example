#include <vector>
#include <fstream>
#include <iostream>
#include "fuzzing_utils.h"

// Global variables
FuzzedDataProvider* global_provider = nullptr;
std::vector<FuzzTestFunc> fuzz_tests;

/*
     Reads an entire file into memory.
     Example usage:

     EntireFile file = read_entire_file_into_memory("some/path/to/file");
     // We can also check file.len
     if (!file.contents) {
         // Could not read the file. Handle error
     }

     // File was read successfully
 */
EntireFile read_entire_file_into_memory(const char* path) {
    EntireFile res = {0};
        long int file_size;
        size_t bytes_read;

    if (!path) {
        fprintf(stderr, "No path was given to read\n");
        return res;
    }

    FILE* file = fopen(path, "rb");
    if (!file) {
        fprintf(stderr, "Could not open %s for reading\n", path);
        goto error;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        fprintf(stderr, "Could not seek to the end of file %s\n", path);
        goto error;
    }

    file_size = ftell(file);
    if (file_size == -1L) {
        fprintf(stderr, "Could not tell the size of file %s\n", path);
        goto error;
    }

    if (fseek(file, 0, SEEK_SET) != 0) {
        fprintf(stderr, "Could not set the cursor to the start of file %s\n", path);
        goto error;
    }

    res.contents = MALLOC(file_size, char);
    if (!res.contents) {
        fprintf(stderr, "Could not allocate memory for storing contents of file %s\n", path);
        goto error;
    }

    bytes_read = fread(res.contents, sizeof(char), file_size, file);
    if (bytes_read != file_size) {
        fprintf(stderr, "Could not read entire file %s\n", path);
        goto error;
    }
    res.len = bytes_read;

    fclose(file);

    return res;

error:
    if (file) {
        fclose(file);
    }

    if (res.contents) {
        free(res.contents);
    }

    return (EntireFile) {0};
}

void RegisterFuzzTest(FuzzTestFunc func) {
    fuzz_tests.push_back(func);
}

void RunFuzzTests(const char* file_path) {
    // Read entire file into memory
    EntireFile file = read_entire_file_into_memory(file_path);
    if (!file.contents) {
        fprintf(stderr, "Failed to open input file: %s\n", file_path);
        return;
    }
	if (file.len < 2) {
        fprintf(stderr, "File is too small\n");
	    return;
    }

    const unsigned char* data = reinterpret_cast<const unsigned char*>(file.contents);
    size_t len = file.len;

    // Create and set up a single FuzzedDataProvider instance
    FuzzedDataProvider provider(data, len);
    global_provider = &provider;  // Set global pointer

    // Run all registered fuzz tests using the same provider
    for (auto& fuzz_test : fuzz_tests) {
        fuzz_test();
    }

    global_provider = nullptr;  // Reset after execution
}
