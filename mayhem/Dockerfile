FROM gcr.io/bazel-public/bazel:latest AS builder
USER root

RUN apt update -y && apt install -y clang

WORKDIR /
ADD . .

RUN llvmpath=$(find -name libclang_rt.fuzzer_no_main-x86_64.a | head -1 | cut -c2-) && sed -i "s|\(.*\)linkopt=\(.*\)|\1linkopt=$llvmpath|" /fuzztest.bazelrc

RUN bazel build --config=libfuzzer //fuzz:fuzztest_calculator

FROM ubuntu
COPY --from=builder /bazel-bin/fuzz/fuzztest_calculator /fuzztest_calculator
