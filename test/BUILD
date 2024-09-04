load("@rules_mayhem//mayhem:mayhem.bzl", "mayhem_run", "mayhem_package")

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

mayhem_package(
    name = "package_test_calculator",
    binary = ":test_calculator",
    testonly = True, # Needed to package test binaries
)

mayhem_run(
    name = "run_test_calculator",
    image = "ubuntu:latest",
    target_path = ":package_test_calculator",
    testonly = True,
)