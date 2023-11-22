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

Currently Mayhem repository is set to `app.mayhem.security`. You can change this to your own instance of Mayhem with `bazel build --define=MAYHEM_URL=<blah.mayhem.security> ...`.

```
bazel run //mayhem:push_fuzz_calculator_image
```

## To build Mayhemfile (and run Mayhem)

```
bazel build //mayhem:mayhem_fuzz_calculator
```
