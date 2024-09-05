load("@rules_mayhem//mayhem:mayhem.bzl", "mayhem_run", "mayhem_package")

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
  deps = [
    "//main:calculator_lib",
  ],
  data = [":testsuite/1"],
  args = ["$(location :testsuite/1)"],
)