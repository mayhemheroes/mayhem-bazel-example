load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "googletest",
    sha256 = "b4870bf121ff7795ba20d20bcdd8627b8e088f2d1dab299a031c1034eddc93d5",
    strip_prefix = "googletest-release-1.11.0",
    urls = ["https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz"],
)

http_archive(
    name = "rules_oci",
    sha256 = "d41d0ba7855f029ad0e5ee35025f882cbe45b0d5d570842c52704f7a47ba8668",
    strip_prefix = "rules_oci-1.4.3",
    url = "https://github.com/bazel-contrib/rules_oci/releases/download/v1.4.3/rules_oci-v1.4.3.tar.gz",
)

load("@rules_oci//oci:dependencies.bzl", "rules_oci_dependencies")

rules_oci_dependencies()

load("@rules_oci//oci:repositories.bzl", "LATEST_CRANE_VERSION", "oci_register_toolchains")

oci_register_toolchains(
    name = "oci",
    crane_version = LATEST_CRANE_VERSION,
    # Uncommenting the zot toolchain will cause it to be used instead of crane for some tasks.
    # Note that it does not support docker-format images.
    # zot_version = LATEST_ZOT_VERSION,
)

http_archive(
    name = "rules_pkg",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_pkg/releases/download/0.9.1/rules_pkg-0.9.1.tar.gz",
        "https://github.com/bazelbuild/rules_pkg/releases/download/0.9.1/rules_pkg-0.9.1.tar.gz",
    ],
    sha256 = "8f9ee2dc10c1ae514ee599a8b42ed99fa262b757058f65ad3c384289ff70c4b8",
)

load("@rules_pkg//:deps.bzl", "rules_pkg_dependencies")
rules_pkg_dependencies()

http_archive(
    name = "rules_mayhem",
    strip_prefix = "rules_mayhem",
    urls = ["https://github.com/ForAllSecure/rules_mayhem/releases/download/0.7.6/rules_mayhem-0.7.6.tar.gz"],
    sha256 = "90e81a3a80d1eecbfacd976f2389a2b1191c440223c8f5f23ab5075a4bafe180",
)

load("@rules_mayhem//mayhem:repositories.bzl", "rules_mayhem_repositories")
rules_mayhem_repositories()

load("@rules_oci//oci:pull.bzl", "oci_pull")

oci_pull(
    name = "ubuntu",
    tag = "latest",
    image = "index.docker.io/library/ubuntu",
    platforms = [
        "linux/amd64",
    ],
)