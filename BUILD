package(default_visibility = ["//visibility:public"])

load("@rules_pkg//pkg:tar.bzl", "pkg_tar")

pkg_tar(
    name = "local_root",
    srcs = glob(["fuzz/**", "main/**", ".bazelrc", "WORKSPACE"]),
    strip_prefix = ".",
)
