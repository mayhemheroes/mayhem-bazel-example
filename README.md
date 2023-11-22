To run libfuzzer example, do:
`bazel run --config=asan-libfuzzer //fuzz:fuzz_calculator_run` 

NOTE: `rules_fuzzing` only works currently with Python 3.9. You can use pyenv to switch to 3.9:

```
pyenv install 3.9.0
pyenv local 3.9.0
```
