#include <CLI/CLI.hpp>
#include <exception>
#include <print>
#include <string>

#include "convertunit.hpp"

auto main(int argc, char* argv[]) -> int {
  try {
    CLI::App app{"Convert between units of length, mass, and temperature"};
    app.set_version_flag("-v,--version", "convertunit 0.1.0");

    double value = 0.0;
    std::string from;
    std::string to;

    app.add_option("value", value, "Numeric value to convert")->required();
    app.add_option("-f,--from", from, "Source unit")->required();
    app.add_option("-t,--to", to, "Target unit")->required();

    CLI11_PARSE(app, argc, argv);

    double result = convertunit::convert(value, from, to);
    std::println("{} {} = {} {}", value, from, result, to);
    return 0;
  } catch (const std::exception& e) {
    std::println(stderr, "Error: {}", e.what());
    return 1;
  }
}
