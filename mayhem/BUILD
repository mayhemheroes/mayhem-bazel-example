load("@io_bazel_rules_docker//container:image.bzl", "container_image")
load("@io_bazel_rules_docker//container:push.bzl", "container_push")
load("@io_bazel_rules_docker//docker/package_managers:download_pkgs.bzl", "download_pkgs")
load("@io_bazel_rules_docker//docker/package_managers:install_pkgs.bzl", "install_pkgs")
load("@io_bazel_rules_docker//docker/util:run.bzl", "container_run_and_commit")
load("@rules_mayhem//mayhem:mayhem.bzl", "mayhem")

download_pkgs(
    name = "libfuzzer_pkgs",
    image_tar = "@ubuntu//image",
    packages = [
        "clang",
        "apt-transport-https",
        "curl",
        "gnupg",
    ],
)

install_pkgs(
    name = "libfuzzer_pkgs_image",
    image_tar = "@ubuntu//image",
    installables_tar = ":libfuzzer_pkgs.tar",
    installation_cleanup_commands = "rm -rf /var/lib/apt/lists/*",
    output_image_name = "libfuzzer_pkgs_image",
)

container_image(
    name = "fuzz_calculator_image",
    testonly = True,
    base = ":libfuzzer_pkgs_image",
    entrypoint = ["/fuzz_calculator_bin"],
    files = ["//fuzz:fuzz_calculator_bin"],
    #tars = ["//:local_root"],
    workdir = "/",
)

# The following actions were an attempt to build the target within the container rather than locally. I couldn't figure out how to get pkg_tar to actually collect directories, however.
# One hack would be to git clone this repository.
#container_run_and_commit(
#    name = "build_libfuzzer_target",
#    commands = [
#        #Download bazel repository
#        "curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor >bazel-archive-keyring.gpg",
#        "mv bazel-archive-keyring.gpg /usr/share/keyrings",
#        "echo 'deb [arch=amd64 signed-by=/usr/share/keyrings/bazel-archive-keyring.gpg] https://storage.googleapis.com/bazel-apt stable jdk1.8' | tee /etc/apt/sources.list.d/bazel.list",
#        #Install bazel
#        "apt update -y && apt install -y bazel",
#        # Build libfuzzer target installation
#        "bazel build --config=asan-libfuzzer //fuzz:fuzz_calculator_run",
#        # Move bin to top level
#        "cp /bazel-bin/fuzz/fuzz_calculator_bin /fuzz_calculator",
#    ],
#    image = ":fuzz_calculator_image.tar",
#)

#container_image(
#    name = "fuzz_calculator_package_image",
#    testonly = True,
#    base = "@ubuntu2004//image",
#    entrypoint = ["/fuzz_calculator_bin"],
#    files = ["//build_libfuzzer_target:"],
#    workdir = "/",
#)

container_push(
    name = "push_fuzz_calculator_image",
    format = "Docker",
    testonly = True,
    image = ":fuzz_calculator_image.tar",
    registry = "$(MAYHEM_URL)",
    repository = "mayhem-bazel-example/calculator",
    tag = "latest",
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
    image = "$MAYHEM_DOCKER_REGISTRY/mayhem-bazel-example/calculator:latest",
)
