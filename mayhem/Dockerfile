FROM ubuntu as builder

# Install required packages
RUN apt update -y && DEBIAN_FRONTEND=noninteractive apt install -y curl git unzip clang jq

# Fetch and install the latest Bazelisk binary
RUN LATEST_URL=$(curl -s https://api.github.com/repos/bazelbuild/bazelisk/releases/latest | jq -r '.assets[] | select(.name | test("bazelisk-linux-amd64")) | .browser_download_url') && \
    curl -Lo /usr/local/bin/bazelisk ${LATEST_URL} && \
    chmod +x /usr/local/bin/bazelisk && \
    ln -s /usr/local/bin/bazelisk /usr/local/bin/bazel

# Get Python 3.9 - required for Bazel
RUN apt install -y software-properties-common && \
    add-apt-repository -y ppa:deadsnakes/ppa && \
    apt update && \
    apt install -y python3.9

RUN useradd -m -d /workspace -s /bin/bash runner
USER runner

WORKDIR /workspace
ADD . .

RUN mkdir out

#Build libFuzzer target
RUN bazel build --config=asan-libfuzzer //fuzz:fuzz_calculator_run
RUN cp ./bazel-bin/fuzz/fuzz_calculator_bin ./out/fuzz_calculator_libfuzzer

#Build uninst target
RUN bazel clean
RUN bazel build --config=uninstrumented //fuzz:fuzz_calculator_run
RUN cp ./bazel-bin/fuzz/fuzz_calculator_bin ./out/fuzz_calculator_uninstrumented

FROM ubuntu
COPY --from=builder /workspace/out/* /
