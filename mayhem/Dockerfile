FROM gcr.io/bazel-public/bazel:latest AS builder
USER root

RUN apt update -y && apt install -y clang

WORKDIR /
ADD . .

RUN bazel build --config=libfuzzer //fuzz:fuzztest_calculator

FROM ubuntu
COPY --from=builder /bazel-bin/fuzz/fuzztest_calculator /fuzztest_calculator
