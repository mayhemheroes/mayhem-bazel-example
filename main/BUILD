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
        "//main:calculator_lib",
    ],
    visibility = ["//visibility:public"],
)
