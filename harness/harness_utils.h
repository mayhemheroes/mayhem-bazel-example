#include <stdio.h>
#include <stdlib.h>

#define MALLOC(num_elements, type) ((type*) malloc((num_elements) * sizeof(type)))
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

#ifdef _MSC_VER
// Disable warnings for using fopen when compiling with MSVC
#define _CRT_SECURE_NO_WARNINGS
#endif

// Structure representing the contents of a file in memory
typedef struct EntireFile {
    char* contents;
    size_t len;
} EntireFile;

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

typedef int (*HarnessFunction)(const char*, size_t);

#define HARNESS(...) \
static HarnessFunction harnesses[] = { \
	__VA_ARGS__ \
}; \
int main(int argc, char* args[]) { \
    ::testing::InitGoogleTest(&argc, args); \
    if (argc > 1) {                         \
        EntireFile file = read_entire_file_into_memory(args[1]); \
        if (!file.contents) { \
            fprintf(stderr, "Failed to open input file: %s\n", args[1]); \
            return 1; \
        } \
	if (file.len < 2) { \
	    return 1; \
        } \
	size_t harness_index = file.contents[0] % ARRAY_LEN(harnesses); \
        return harnesses[harness_index](file.contents + 1, file.len - 1); \
    } \
    return RUN_ALL_TESTS(); \
}