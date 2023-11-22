load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@rules_oci//oci:defs.bzl", "oci_image", "oci_push", "oci_tarball")
load("@rules_mayhem//mayhem:mayhem.bzl", "mayhem")

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
    repo_tags = ["mayhem-bazel-example/calculator:latest"],
    testonly = True,
)

oci_push(
    name = "push_fuzz_calculator_image",
    image = ":fuzz_calculator_image",
    remote_tags = ["latest"],
    #repository = "$(MAYHEM_URL):5000/mayhem-bazel-example/calculator",
    repository = "ghcr.io/ForAllSecure/mayhem-bazel-example/calculator",
    testonly = True,
)

mayhem(
    name = "mayhem_fuzz_calculator",
    run = True,
    project = "mayhem-bazel-example",
    target = "fuzz_calculator",
    command = "/fuzz_calculator_bin @@",
    duration = "90",
    sanitizer = "true",
    libfuzzer = "false",
    #image = "$MAYHEM_DOCKER_REGISTRY/mayhem-bazel-example/calculator:latest",
    image = "ghcr.io/ForAllSecure/mayhem-bazel-example/calculator:latest",
)
