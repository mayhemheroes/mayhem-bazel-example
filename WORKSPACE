load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_fuzzing",
    sha256 = "d9002dd3cd6437017f08593124fdd1b13b3473c7b929ceb0e60d317cb9346118",
    strip_prefix = "rules_fuzzing-0.3.2",
    urls = ["https://github.com/bazelbuild/rules_fuzzing/archive/v0.3.2.zip"],
)
load("@rules_fuzzing//fuzzing:repositories.bzl", "rules_fuzzing_dependencies")
rules_fuzzing_dependencies()
load("@rules_fuzzing//fuzzing:init.bzl", "rules_fuzzing_init")
rules_fuzzing_init()
load("@fuzzing_py_deps//:requirements.bzl", "install_deps")
install_deps()

http_archive(
    name = "io_bazel_rules_docker",
    sha256 = "b1e80761a8a8243d03ebca8845e9cc1ba6c82ce7c5179ce2b295cd36f7e394bf",
    urls = ["https://github.com/bazelbuild/rules_docker/releases/download/v0.25.0/rules_docker-v0.25.0.tar.gz"],
)
load(
    "@io_bazel_rules_docker//repositories:repositories.bzl",
    container_repositories = "repositories",
)
container_repositories()

load(
  "@io_bazel_rules_docker//repositories:go_repositories.bzl",
  container_go_deps = "go_deps",
)
container_go_deps()
load("@io_bazel_rules_docker//container:pull.bzl", "container_pull")
load("@io_bazel_rules_docker//container:push.bzl", "container_push")

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
  strip_prefix = "rules_mayhem-rules_mayhem-0.4",
  urls = ["https://github.com/xansec/rules_mayhem/archive/rules_mayhem-0.4.tar.gz"],
  sha256 = "5b643bb3a8628982d13f24abb011c56d26f3b8c170d6ebaef0633889dc9d5931",
)

load("@rules_mayhem//mayhem:mayhem.bzl", "mayhem")

container_pull(
    name = "ubuntu2004",
    digest = "sha256:27a5b5335a18890fd424e71878a86124d930284ac962dc167ff7f8676e78a573",
    registry = "l.gcr.io",
    repository = "google/ubuntu2004",
    # tag field is ignored since digest is set
    tag = "latest",
)

container_pull(
    name = "ubuntu",
    digest = "sha256:ca5534a51dd04bbcebe9b23ba05f389466cf0c190f1f8f182d7eea92a9671d00",
    registry = "docker.io",
    repository = "library/ubuntu",
    # tag field is ignored since digest is set
    tag = "latest",
)
