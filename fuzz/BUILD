package(default_visibility = ["//visibility:public"])

load("@rules_fuzzing//fuzzing:cc_defs.bzl", "cc_fuzz_test")

cc_fuzz_test(
    name = "fuzz_calculator",
    srcs = ["fuzz_calculator.cc"],
    deps = [
        "//main:calculator_lib",
    ],
)
