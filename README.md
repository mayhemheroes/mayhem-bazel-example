# End to end Bazel + Mayhem example.

NOTE: To use `rules_fuzzing`, you must have Python 3.9. You can use `pyenv` to switch:
```
pyenv install 3.9.0
pyenv global 3.9.0
```

# Uninstrumented target

## To build calculator target

```
bazel build //main:calculator
```

## To package calculator target

```
bazel build //mayhem:package_calculator
```

## To run calculator target

```
bazel build --action_env=MAYHEM_URL=$MAYHEM_URL --action_env=MAYHEM_TOKEN=$MAYHEM_TOKEN //mayhem:run_package_calculator 
```

The above works with the test target `//test:test_calculator` as well.

### Note on authentication with Mayhem

Commands like `mayhem run` need to be authenticated to the Mayhem server. You can change specify this with the `--action_env` parameter: 
```
bazel build --action_env=MAYHEM_URL=<blah.mayhem.security> --action_env=MAYHEM_TOKEN=<token> ...
``` 

# LibFuzzer target

## To build libfuzzer target

```
bazel build --config=libfuzzer //fuzz:fuzz_calculator
```

### To run libfuzzer target locally

```
bazel run --config=libfuzzer //fuzz:fuzz_calculator_run
```

## To build docker image with libfuzzer target

```
bazel build --config=libfuzzer //mayhem:fuzz_calculator_image
```

## To push docker image with libfuzzer target

```
bazel run --config=libfuzzer //mayhem:push_fuzz_calculator_image
```

## To run Mayhem against docker image for libfuzzer target

```
bazel build --config=libfuzzer --action_env=MAYHEM_URL=$MAYHEM_URL --action_env=MAYHEM_TOKEN=$MAYHEM_TOKEN //mayhem:run_fuzz_calculator_image
```

# Regression Testing

## To run Mayhem on regression tests only, wait for the run to finish, and output a SARIF report

```
bazel build --config=libfuzzer --action_env=MAYHEM_URL=$MAYHEM_URL --action_env=MAYHEM_TOKEN=$MAYHEM_TOKEN //mayhem:run_test_calculator_package
```


# Code Coverage

You can download code coverage generated by Mayhem with the `mayhem_download()` rule:

```
mayhem_download(
    name = "download_combined_test_calculator_results",
    owner = "training",
    project = "mayhem-bazel-example",
    target = "test_calculator_package",
    output_dir = "combined_test_calculator-pkg",
    testonly = True,
)
```

Then, run the following command to download the code coverage:

```
bazel build --action_env=MAYHEM_URL=$MAYHEM_URL --action_env=MAYHEM_TOKEN=$MAYHEM_TOKEN //test:download_combined_test_calculator_results
```

The code coverage will be downloaded to `bazel-bin/test/combined_test_calculator-pkg/coverage.tgz`.
If you'd like to generate coverage manually, you can do this with Bazel, but you'll have to run each individual file under the `testsuite` directory. An easy way to do this is:

```bash
for test in $(ls ./bazel-bin/test/combined_test_calculator-pkg/testsuite); do bazel coverage --combined_report=lcov //test:combined_test_calculator --test_arg=test/combined_test_calculator-pkg/testsuite/$test; done
```