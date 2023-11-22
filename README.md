##Fuzztest

To execute fuzztest example, run:
`bazel test --config=fuzztest //fuzz:fuzztest_calculator`

##Fuzztest with libFuzzer

To execute fuzztest with libFuzzer, run:
`bazel test --config=libfuzzer //fuzz:fuzztest_calculator`
