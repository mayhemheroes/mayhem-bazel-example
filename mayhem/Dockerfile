FROM gcr.io/bazel-public/bazel:latest AS builder
USER root

RUN apt update -y && apt install -y clang

RUN mkdir /out

WORKDIR /
ADD . .

#Build libFuzzer target
RUN bazel build --config=asan-libfuzzer //fuzz:fuzz_calculator_run
RUN cp /bazel-bin/fuzz/fuzz_calculator_bin /out/fuzz_calculator_libfuzzer

#Build uninst target
RUN bazel clean
RUN bazel build --config=uninstrumented //fuzz:fuzz_calculator_run
RUN cp /bazel-bin/fuzz/fuzz_calculator_bin /out/fuzz_calculator_uninstrumented

FROM ubuntu
COPY --from=builder /out/* /
