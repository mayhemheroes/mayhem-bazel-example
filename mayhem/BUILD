load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@rules_oci//oci:defs.bzl", "oci_image", "oci_push", "oci_tarball")
load("@rules_mayhem//mayhem:mayhem.bzl", "mayhemfile", "mayhem_run", "mayhem_package")

# pkg_tar(
#     name = "fuzz_calculator_tar",
#     srcs = ["//fuzz:fuzz_calculator_bin"],
#     mode = "0755",
#     testonly = True,
# )

# oci_image(
#   name = "fuzz_calculator_image",
#   base = "@ubuntu",
#   entrypoint = ["/fuzz_calculator_bin"],
#   tars = [":fuzz_calculator_tar"],
#   testonly = True,
#   user = "root",
#   workdir = "/",
# )

# oci_tarball(
#     name = "fuzz_calculator_tarball",
#     image = ":fuzz_calculator_image",
#     repo_tags = ["mayhem-bazel-example:latest"],
#     testonly = True,
# )

# oci_push(
#     name = "push_fuzz_calculator_image",
#     image = ":fuzz_calculator_image",
#     remote_tags = ["latest"],
#     #repository = "$(MAYHEM_URL):5000/mayhem-bazel-example",
#     repository = "ghcr.io/forallsecure/mayhem-bazel-example",
#     testonly = True,
# )

# mayhemfile(
#     name = "fuzz_calculator_mayhemfile",
#     owner = "training",
#     project = "mayhem-bazel-example",
#     target = "fuzz_calculator",
#     cmd = "/fuzz_calculator_bin @@",
#     duration = "90",
#     sanitizer = "true",
#     libfuzzer = "false",
#     #image = "$MAYHEM_DOCKER_REGISTRY/mayhem-bazel-example:latest",
#     image = "ghcr.io/forallsecure/mayhem-bazel-example:latest",
# )

# mayhem_run(
#     name = "run_docker_fuzz_calculator",
#     target_path = ".",
#     mayhemfile = ":fuzz_calculator_mayhemfile",
# )

mayhem_package(
    name = "package_calculator",
    binary = "//main:calculator",
)

mayhem_run(
    name = "run_package_calculator",
    image = "ubuntu:latest",
    target_path = ":package_calculator",

)

# mayhem_package(
#     name = "package_fuzz_calculator",
#     binary = "//fuzz:fuzz_calculator_bin",
#     testonly = True, # this is needed to work around testonly restrictions
# )

# mayhem_run(
#     name = "run_package_fuzz_calculator",
#     image = "chainguard/glibc-dynamic",
#     target_path = ":package_fuzz_calculator",
#     testonly = True,
# )

mayhem_package(
    name = "package_test_calculator",
    binary = "//test:test_calculator",
    testonly = True, # Needed to package test binaries
)

mayhem_run(
    name = "run_package_test_calculator",
    image = "ubuntu:latest",
    target_path = ":package_test_calculator",
    testonly = True,
)