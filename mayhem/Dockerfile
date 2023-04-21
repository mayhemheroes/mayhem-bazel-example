FROM gcr.io/bazel-public/bazel:latest AS builder
USER root

RUN apt update -y && apt install -y clang

WORKDIR /
ADD . .

RUN bazel build --config=libfuzzer //fuzz:fuzz_calculator_run

FROM ubuntu
COPY --from=builder /bazel-bin/fuzz/fuzz_calculator_bin /fuzz_calculator
