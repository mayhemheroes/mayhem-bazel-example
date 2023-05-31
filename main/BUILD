cc_library(
    name = "calculator_lib",
    srcs = ["calculator.c"],
    hdrs = ["calculator.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "calculator",
    srcs = ["main.c"],
    deps = [
        ":calculator_lib",
        "//main:calculator_lib",
    ],
)
