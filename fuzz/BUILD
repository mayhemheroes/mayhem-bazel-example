cc_library(
    name = "calculator_lib",
    srcs = ["calculator.c"],
    hdrs = ["calculator.h"],
)

cc_binary(
    name = "fuzz_calculator",
    srcs = ["fuzz_calculator.c"],
    deps = [
        ":calculator_lib",
    ],
)
