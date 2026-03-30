# cpp-template

A C++ project template.

## Build

Requires LLVM 22, CMake, and Ninja.

```sh
export CC=clang-22
export CXX=clang++-22
cmake -B build -G Ninja
cmake --build build
```

## Test

```sh
ctest --test-dir build
```

Run a single test:

```sh
ctest --test-dir build -R "test name"
```

## Format

```sh
cmake --build build --target format
```

Fix formatting (not just check):

```sh
clang-format-22 -i <files>
```

## Lint

```sh
cmake --build build --target lint
```

## Project layout

- `include/` — Public headers (`.hpp`) that form the library's API.
- `src/` — Source files (`.cpp`) and private headers (`.hpp`).
- `test/` — Unit tests using Catch2 (one test file per source file).
- `CMakeLists.txt` — Build configuration, dependencies, format/lint/docs targets.
- `.clang-format` — Formatter config
- `.clang-tidy` — Linter config

## Code style

- Use modern C++23: `std::println`, `std::string_view`, structured bindings, trailing return types, etc.
- Use `#pragma once` for header guards.

## External references

- [C++ Core Guidelines](https://raw.githubusercontent.com/isocpp/CppCoreGuidelines/refs/heads/master/CppCoreGuidelines.md)
