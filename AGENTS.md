# AGENTS.md

This is a C++ project template.

## Project structure

- `include/` — Public headers (`.hpp`) that form the library's API.
- `src/` — Source files (`.cpp`) and private headers (`.hpp`).
- `test/` — Unit tests using Catch2.
- `CMakeLists.txt` — Build configuration, dependencies, format/lint/docs targets.
- `CMakePresets.json` — Configure, build, and test presets for debug/release workflows.
- `.clang-format` — Formatter configuration.
- `.clang-tidy` — Linter configuration.
- `.clangd` — LSP configuration.

## Code style

- Use modern C++23: `std::println`, `std::string_view`, structured bindings, trailing return types, etc.
- Use `#pragma once` for header guards.

## Build

```sh
cmake --preset debug
cmake --build --preset debug
```

- Requires LLVM 22, CMake 3.20+, and Ninja.
- For optimized builds, run `cmake --preset release` once to set up `build/release`, then `cmake --build --preset release` to compile it.
- Prefer CMake presets over environment variables:
  * `CMakePresets.json` pins `clang-22` and `clang++-22`.
- `cmake -B build -G Ninja` works, but it defaults the build type to `Debug`:
  * -B build tells CMake to put generated build files in the `build/` directory.
  * -G Ninja tells CMake to use Ninja as the build tool.

## Test

```sh
ctest --preset debug
```

Run a single test:

```sh
ctest --preset debug -R "test name"
```

## Formatting

```sh
cmake --build --preset debug --target format
```

To fix formatting issues:

```sh
clang-format-22 -i <files>
```

## Linting

```sh
cmake --build --preset debug --target lint
```

## Development

- Re-run configure after changing `CMakeLists.txt` or `CMakePresets.json`.
- For new features, update code and the corresponding test file together.

## References

- [C++ Core Guidelines](https://raw.githubusercontent.com/isocpp/CppCoreGuidelines/refs/heads/master/CppCoreGuidelines.md)
