load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_fuzzing",
    sha256 = "ff52ef4845ab00e95d29c02a9e32e9eff4e0a4c9c8a6bcf8407a2f19eb3f9190",
    strip_prefix = "rules_fuzzing-0.4.1",
    urls = ["https://github.com/bazelbuild/rules_fuzzing/releases/download/v0.4.1/rules_fuzzing-0.4.1.zip"],
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
    strip_prefix = "rules_mayhem-rules_mayhem-0.5",
    urls = ["https://github.com/ForAllSecure/rules_mayhem/archive/rules_mayhem-0.5.tar.gz"],
    sha256 = "c3c6f022fc7a7d7f1f7a23475742e626c5274fe3a75f1ef2ebac7455805c5712",
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
