package(default_visibility = ["//visibility:public"])

load("@rules_pkg//pkg:tar.bzl", "pkg_tar")

pkg_tar(
    name = "local_root",
    srcs = glob(["fuzz/**", "main/**", ".bazelrc", "WORKSPACE"]),
    strip_prefix = ".",
)

platform(
    name = "x64_windows-clang-cl",
    constraint_values = [
        "@platforms//cpu:x86_64",
        "@platforms//os:windows",
        "@bazel_tools//tools/cpp:clang-cl",
    ],
)