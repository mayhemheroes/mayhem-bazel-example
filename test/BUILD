load("@rules_mayhem//mayhem:mayhem.bzl", "mayhem_download")

package(default_visibility = ["//visibility:public"])

cc_test(
  name = "gtest_calculator",
  size = "small",
  srcs = ["gtest_calculator.cc"],
  deps = [
    "@googletest//:gtest_main",
    "//main:calculator_lib",
  ],
)

cc_test(
  name = "test_calculator",
  size = "small",
  srcs = ["test_calculator.cc"],
  copts = ["-ftest-coverage", "-fprofile-arcs"],
  linkopts = ["-lgcov", "--coverage"],
  deps = [
    "//main:calculator_lib",
  ],
  data = [":testsuite"],
)

cc_test(
  name = "combined_test_calculator",
  size = "small",
  srcs = ["combined_test_calculator.cc"],
  copts = ["-ftest-coverage", "-fprofile-arcs"],
  linkopts = ["-lgcov", "--coverage"],
  deps = [
    "@googletest//:gtest_main",
    "//main:calculator_lib",
  ],
  data = [":testsuite", "//test:download_combined_test_calculator_results"],
)

cc_test(
  name = "harness_utils_test_calculator",
  size = "small",
  srcs = ["harness_utils_test_calculator.cc"],
  copts = ["-ftest-coverage", "-fprofile-arcs"],
  linkopts = ["-lgcov", "--coverage"],
  deps = [
    "@googletest//:gtest_main",
    "//main:calculator_lib",
    "//harness:harness_utils",
  ],
  data = [":testsuite", "//test:download_combined_test_calculator_results"],
)

cc_test(
  name = "fuzzing_utils_test_calculator",
  size = "small",
  srcs = ["fuzzing_utils_test_calculator.cc"],
  copts = ["-ftest-coverage", "-fprofile-arcs"],
  linkopts = ["-lgcov", "--coverage"],
  deps = [
    "@googletest//:gtest_main",
    "//main:calculator_lib",
    "//harness:fuzzing_utils",
  ],
  data = [":testsuite", "//test:download_combined_test_calculator_results"],
)

mayhem_download(
    name = "download_combined_test_calculator_results",
    owner = "training",
    project = "mayhem-bazel-example",
    target = select({
        "@platforms//os:windows": "test_calculator_package_exe",
        "//conditions:default": "test_calculator_package",
    }),
    output_dir = "combined_test_calculator-pkg",
    testonly = True,
)