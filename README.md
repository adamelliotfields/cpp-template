# cpp-template

An opinionated C++ project template with [CMake](https://github.com/kitware/cmake), [Ninja](https://github.com/ninja-build/ninja), [Catch2](https://github.com/catchorg/Catch2), [CLI11](https://github.com/CLIUtils/CLI11), and [Doxygen](https://github.com/doxygen/doxygen).

## OS Support

Only Debian/Ubuntu/Mint (including WSL) are supported.

## Dependencies

> [!NOTE]
> Catch2 and CLI11 are installed via CMake `FetchContent`.

```sh
apt install cmake doxygen gdb graphviz ninja-build
```

### LLVM

You need to install [LLVM](https://llvm.org) 22.x system-wide. See [apt.llvm.org](https://apt.llvm.org):

```sh
cd /tmp
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 22
rm -f llvm.sh
```

## Project Structure

```
.
├── .clang-format      # formatter configuration
├── .clang-tidy        # linter configuration
├── .clangd            # LSP configuration
├── CMakeLists.txt     # build configuration and targets
├── CMakePresets.json  # configure, build, and test presets
├── include
│   └── *.hpp          # public headers
├── src
│   ├── *.hpp          # private headers
│   └── *.cpp          # source code
└── test
    └── *.cpp          # unit tests
```

Conventionally, public headers go in `include/your_lib/*.hpp` so users can `#include your_lib/your_header.hpp`. C++ header files can have the `.h` or `.hpp` extension (or `.cuh` for CUDA).

## Building

> [!NOTE]
> This project targets ISO C++23 and disables GNU compiler extensions by default. See [CMakeLists.txt](./CMakeLists.txt):

```sh
cmake --preset debug
cmake --build --preset debug
```

The `debug` preset is the default development path. It gives you debug symbols and avoids optimization, which makes stepping through code easier. For optimized builds run:

```sh
cmake --preset release
cmake --build --preset release
```

## Formatting

```sh
cmake --build --preset debug --target format
```

## Linting

```sh
cmake --build --preset debug --target lint
```

## Testing

Run all tests:

```sh
ctest --preset debug
```

Run a single test:

```sh
ctest --preset debug -R "Kilometers to meters"
```

## Documentation

```sh
cmake --build --preset debug --target docs
python3 -m http.server -d build/html
```

If you want docs to generate on every build:

```sh
sed -i 's/doxygen_add_docs(docs include src)/doxygen_add_docs(docs ALL include src)/' CMakeLists.txt
```

## VS Code

> [!NOTE]
> Ensure the LLVM bin path in this file matches your system.

The [`settings.json`](./.vscode/settings.json) does the following:

- Disables the built-in language server
- Sets `clangd` as the language server
- Sets `clang-format` as the formatter
- Sets `clang-tidy` as the linter
- Enables format-on-save

The workspace also includes:

- [`extensions.json`](./.vscode/extensions.json)
- [`launch.json`](./.vscode/launch.json) for debugging
- [`tasks.json`](./.vscode/tasks.json) for configure, build, and test commands

## Agents

Edit [`AGENTS.md`](./AGENTS.md) after creating a project from this template. Add project-specific instructions and keep the development workflow accurate.

### OpenCode

> [!NOTE]
> The project [`.clangd`](./.clangd) relies on the `build` directory for `compile_commands.json`. Run `cmake --preset debug` first.

OpenCode disables LSPs by default. To enable `clangd` support, add an OpenCode config at `opencode.json` or `.opencode/opencode.json` with:

```json
{
  "$schema": "https://opencode.ai/config.json",
  "lsp": {
    "clangd": {
      "command": ["clangd"]
    }
  }
}
```

## Demo

The demo app is a unit converter CLI.

Remove `include/convertunit.hpp`, `src/convertunit.cpp`, and `test/convertunit_test.cpp`:

```sh
rm -f include/convertunit.hpp src/convertunit.cpp test/convertunit_test.cpp
```

Modify `CMakeLists.txt` and `src/main.cpp`, replacing `your_app` with your project name:

```sh
sed -i 's/convertunit/your_app/g' CMakeLists.txt src/main.cpp
```

Finally, edit [launch.json](./.vscode/launch.json) to debug your app accordingly.
