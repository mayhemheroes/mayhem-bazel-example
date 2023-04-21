FROM gcr.io/bazel-public/bazel:latest AS builder

WORKDIR /
ADD . .

RUN bazel build --config=asan-libfuzzer //fuzz:fuzz_calculator_run

FROM ubuntu
COPY --from=builder /bazel-bin/fuzz/fuzz_calculator_run /fuzz_calculator
