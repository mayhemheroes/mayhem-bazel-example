#ifndef FUZZING_UTILS_H
#define FUZZING_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <fuzzer/FuzzedDataProvider.h>

#ifdef _MSC_VER
// Disable warnings for using fopen when compiling with MSVC
#define _CRT_SECURE_NO_WARNINGS
#endif

#define MALLOC(num_elements, type) ((type*) malloc((num_elements) * sizeof(type)))

extern FuzzedDataProvider* global_provider;

#define INIT_FUZZ_TEST \
    FuzzedDataProvider& provider = *global_provider; \
    if (!global_provider) { \
        fprintf(stderr, "Error: FuzzedDataProvider not initialized!\n"); \
        return; \
    }

// Bunch of variable replacement
#define FUZZ_TEST(test_group, test_name) \
    void test_group##_##test_name##_FuzzTest(); \
    struct test_group##_##test_name##_FuzzTestRunner { \
        test_group##_##test_name##_FuzzTestRunner() { RegisterFuzzTest(test_group##_##test_name##_FuzzTest); } \
    } test_group##_##test_name##_instance; \
    void test_group##_##test_name##_FuzzTest()

typedef void (*FuzzTestFunc)();

// Structure representing the contents of a file in memory
typedef struct EntireFile {
    char* contents;
    size_t len;
} EntireFile;

EntireFile read_entire_file_into_memory(const char* path);
void RegisterFuzzTest(FuzzTestFunc func);
void RunFuzzTests(const char* file_path);

#endif // FUZZING_UTILS_H
