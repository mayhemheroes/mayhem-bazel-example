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
bazel build //mayhem:fuzz_calculator_image
```

## To push docker image with libfuzzer target

Commands like `mayhem run` need to be authenticated to the Mayhem server. You can change specify this with the `--action_env` parameter: 
```
bazel build --action_env=MAYHEM_URL=<blah.mayhem.security> --action_env=MAYHEM_TOKEN=<token> ...
``` 

```
bazel run --action_env=MAYHEM_URL=$MAYHEM_URL --action_env=MAYHEM_TOKEN=$MAYHEM_TOKEN //mayhem:push_fuzz_calculator_image
```

## To build Mayhemfile for libfuzzer target (and run Mayhem)

```
bazel build --action_env=MAYHEM_URL=$MAYHEM_URL --action_env=MAYHEM_TOKEN=$MAYHEM_TOKEN //mayhem:mayhem_fuzz_calculator
```

## To run Mayhem with package instead of docker image

```
bazel build --config=libfuzzer --action_env=MAYHEM_URL=$MAYHEM_URL --action_env=MAYHEM_TOKEN=$MAYHEM_TOKEN //mayhem:run_package_fuzz_calculator
```


