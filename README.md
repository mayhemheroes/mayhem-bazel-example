# End to end Bazel + Mayhem example.

NOTE: To use `rules_fuzzing`, you must have Python 3.9. You can use `pyenv` to switch:
```
pyenv install 3.9.0
pyenv global 3.9.0
```

## To build calculator target

```
bazel build //main:calculator
```

## To build fuzz target

```
bazel build //fuzz:fuzz_calculator
```

### To fuzz locally

```
bazel run --config=asan-libfuzzer //fuzz:fuzz_calculator_run
```

## To build docker image

```
bazel build //mayhem:fuzz_calculator_image
```

## To push docker image

Commands like `mayhem run` need to be authenticated to the Mayhem server. You can change specify this with the `--action_env` parameter: 
```
bazel build --action_env=MAYHEM_URL=<blah.mayhem.security> --action_env=MAYHEM_TOKEN=<token> ...
``` 

```
bazel run --action_env=MAYHEM_URL=$MAYHEM_URL --action_env=MAYHEM_TOKEN=$MAYHEM_TOKEN //mayhem:push_fuzz_calculator_image
```

## To build Mayhemfile (and run Mayhem)

```
bazel build --action_env=MAYHEM_URL=$MAYHEM_URL --action_env=MAYHEM_TOKEN=$MAYHEM_TOKEN //mayhem:mayhem_fuzz_calculator
```
