load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@rules_oci//oci:defs.bzl", "oci_image", "oci_push", "oci_tarball")
load("@rules_mayhem//mayhem:mayhem.bzl", "mayhem_run", "mayhem_package")

package(default_visibility = ["//visibility:public"])

# Docker example

pkg_tar(
    name = "fuzz_calculator_tar",
    srcs = ["//fuzz:fuzz_calculator_bin"],
    mode = "0755",
    testonly = True,
)

oci_image(
  name = "fuzz_calculator_image",
  base = "@ubuntu",
  entrypoint = ["/fuzz_calculator_bin"],
  tars = [":fuzz_calculator_tar"],
  testonly = True,
  user = "root",
  workdir = "/",
)

oci_tarball(
    name = "fuzz_calculator_tarball",
    image = ":fuzz_calculator_image",
    repo_tags = ["mayhem-bazel-example:latest"],
    testonly = True,
)

oci_push(
    name = "push_fuzz_calculator_image",
    image = ":fuzz_calculator_image",
    remote_tags = ["latest"],
    #repository = "$(MAYHEM_URL):5000/mayhem-bazel-example",
    repository = "ghcr.io/forallsecure/mayhem-bazel-example",
    testonly = True,
)

mayhem_run(
    name = "run_fuzz_calculator_image",
    owner = "training",
    project = "mayhem-bazel-example",
    target = "fuzz_calculator_image",
    cmd = "/fuzz_calculator_bin",
    duration = "90",
    sanitizer = "true",
    libfuzzer = "false",
    image = "ghcr.io/forallsecure/mayhem-bazel-example:latest",
)

# Calculator Standalone binary example

mayhem_package(
    name = "calculator_package",
    binary = "//main:calculator",
)

mayhem_run(
    name = "run_calculator_package",
    owner = "training",
    project = "mayhem-bazel-example",
    target = select({
        "@platforms//os:windows": "calculator_package_exe",
        "//conditions:default": "calculator_package",
    }),
    image = "ubuntu:latest",
    duration = "120",
    target_path = ":calculator_package",
)

# Calculator libFuzzer example

mayhem_package(
    name = "fuzz_calculator_package",
    binary = "//fuzz:fuzz_calculator_bin",
    testonly = True, # this is needed to work around testonly restrictions
)

mayhem_run(
    name = "run_fuzz_calculator_package",
    owner = "training",
    project = "mayhem-bazel-example",
    target = select({
        "@platforms//os:windows": "fuzz_calculator_package_exe",
        "//conditions:default": "fuzz_calculator_package",
    }),
    image = "kubler/glibc",
    target_path = ":fuzz_calculator_package",
    testonly = True,
)

# Calculator gtest integration example

mayhem_package(
    name = "test_calculator_package",
    binary = "//test:combined_test_calculator",
    testonly = True, # Needed to package test binaries
)

mayhem_run(
    name = "run_test_calculator_package",
    owner = "training",
    project = "mayhem-bazel-example",
    target = select({
        "@platforms//os:windows": "test_calculator_package_exe",
        "//conditions:default": "test_calculator_package",
    }),
    image = "kubler/glibc",
    target_path = ":test_calculator_package",
    wait = True,
    # fail_on_defects = True,
    sarif = "test_calculator_package.sarif",
    regression = True,
    duration = "60",
    testonly = True,
)

# Calculator FUZZ_TEST macro example

mayhem_package(
    name = "fuzzing_utils_test_calculator_package",
    binary = "//test:fuzzing_utils_test_calculator",
    testonly = True, # Needed to package test binaries
)

mayhem_run(
    name = "run_fuzzing_utils_test_calculator_package",
    owner = "training",
    project = "mayhem-bazel-example",
    target = select({
        "@platforms//os:windows": "fuzzing_utils_test_calculator_package_exe",
        "//conditions:default": "fuzzing_utils_test_calculator_package",
    }),
    image = "kubler/glibc",
    target_path = ":fuzzing_utils_test_calculator_package",
    duration = "120",
    testonly = True,
)