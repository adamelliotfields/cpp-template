# cpp-template

A C++ project template with [CMake](https://github.com/kitware/cmake), [Ninja](https://github.com/ninja-build/ninja), [Catch2](https://github.com/catchorg/Catch2), [CLI11](https://github.com/CLIUtils/CLI11), and [Doxygen](https://github.com/doxygen/doxygen).

## Dependencies

```sh
apt install cmake doxygen graphviz ninja-build
```

_Catch2 and CLI11 are installed via CMake `FetchContent`._

## Building

```sh
export CC=clang-22
export CXX=clang++-22
cmake -B build -G Ninja
cmake --build build
```

## Formatting

```sh
cmake --build build --target format
```

## Linting

```sh
cmake --build build --target lint
```

## Testing

```sh
ctest --test-dir build
```

## Documentation

```sh
cmake --build build --target docs
python3 -m http.server -d build/html
```

If you want docs to generate on every build:

```sh
sed -i 's/doxygen_add_docs(docs include src)/doxygen_add_docs(docs ALL include src)/' CMakeLists.txt
```

## Organization

```
.
├── .clang-format   # formatter
├── .clang-tidy     # linter
├── .clangd         # language server
├── CMakeLists.txt  # build configuration
├── include
│   └── *.hpp       # public headers
├── src
│   ├── *.hpp       # private headers
│   └── *.cpp       # source code
└── test
    └── *.cpp       # unit tests
```

Conventionally, public headers go in `include/your_lib/*.hpp` so users can `#include your_lib/your_header.hpp` when it is installed.

C++ header files can be either `.h` or `.hpp` (or `.cuh` for CUDA).

## VS Code

> [!NOTE]
> You need to change the LLVM bin path in this file to match your system.

The [`settings.json`](./.vscode/settings.json) does the following:

- Disables built-in language server
- Sets `clangd` as the language server
- Sets `clang-format` as the formatter
- Enables format-on-save
- Enables `clang-tidy` linting

### Extensions

Install [`cpptools`](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) and [`vscode-clangd`](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd) for syntax highlighting and language features. Install [`cmake`](https://marketplace.visualstudio.com/items?itemName=twxs.cmake) for CMake support.

## Demo

The demo app is a unit converter CLI.

Remove `include/convertunit.hpp`, `src/convertunit.cpp`, and `test/convertunit_test.cpp`:

```sh
rm -f include/convertunit.hpp src/convertunit.cpp test/convertunit_test.cpp
```

Modify `CMakeLists.txt` and `src/main.cpp` to make it your own:

```sh
sed -i 's/convertunit/your_app/g' CMakeLists.txt src/main.cpp
```
