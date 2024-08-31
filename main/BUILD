package(default_visibility = ["//visibility:public"])

cc_library(
    name = "calculator_lib",
    srcs = ["calculator.c"],
    hdrs = ["calculator.h"],
)

cc_binary(
    name = "calculator",
    srcs = ["main.c"],
    deps = [
        "//main:calculator_lib",
    ],
)
