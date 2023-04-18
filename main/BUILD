cc_library(
    name = "calculator-lib",
    srcs = ["calculator.c"],
    hdrs = ["calculator.h"],
)

cc_binary(
    name = "calculator",
    srcs = ["main.c"],
    deps = [
        ":calculator-lib",
    ],
)
