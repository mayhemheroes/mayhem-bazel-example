# End to end Bazel + Mayhem example.

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

Currently Mayhem repository is set to `demo.forallsecure.com`. You may want to change this to your own instance of Mayhem.

```
bazel run //mayhem:push_fuzz_calculator_image
```

## To build Mayhemfile (and run Mayhem)

```
bazel build //mayhem:mayhem_fuzz_calculator
```
