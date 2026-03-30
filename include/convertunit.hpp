#pragma once

#include <array>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

/// @brief Unit conversion library supporting length, mass, and temperature.
namespace convertunit {

namespace detail {

using unit_factor = std::pair<std::string_view, double>;

inline constexpr std::array<unit_factor, 8> length_to_meter = {{
  {"m", 1.0},
  {"km", 1000.0},
  {"cm", 0.01},
  {"mm", 0.001},
  {"mi", 1609.344},
  {"yd", 0.9144},
  {"ft", 0.3048},
  {"in", 0.0254},
}};

inline constexpr std::array<unit_factor, 5> mass_to_kg = {{
  {"kg", 1.0},
  {"g", 0.001},
  {"mg", 0.000001},
  {"lb", 0.45359237},
  {"oz", 0.028349523125},
}};

template <std::size_t Size>
inline auto find_factor(
  std::string_view unit,
  const std::array<unit_factor, Size>& table
) -> const double* {
  for (const auto& [name, factor] : table) {
    if (name == unit) return &factor;
  }

  return nullptr;
}

inline auto is_temperature_unit(std::string_view unit) -> bool {
  return unit == "C" || unit == "F" || unit == "K";
}

inline auto convert_temperature(
  double value,
  std::string_view from,
  std::string_view to
) -> double {
  double celsius = 0.0;
  if (from == "C") {
    celsius = value;
  } else if (from == "F") {
    celsius = (value - 32.0) * 5.0 / 9.0;
  } else if (from == "K") {
    celsius = value - 273.15;
  }

  if (to == "C") return celsius;
  if (to == "F") return (celsius * 9.0 / 5.0) + 32.0;
  if (to == "K") return celsius + 273.15;

  throw std::invalid_argument("Unknown temperature unit: " + std::string(to));
}

template <std::size_t Size>
inline auto convert_via_table(
  double value,
  std::string_view from,
  std::string_view to,
  const std::array<unit_factor, Size>& table
) -> double {
  const double* from_factor = find_factor(from, table);
  const double* to_factor = find_factor(to, table);

  if (from_factor == nullptr || to_factor == nullptr) {
    throw std::invalid_argument(
      "Unknown unit: " + std::string(from) + " or " + std::string(to)
    );
  }

  return value * *from_factor / *to_factor;
}

}  // namespace detail

/// @brief Convert a numeric value between units.
///
/// Supported units:
/// - **Length:** m, km, cm, mm, mi, yd, ft, in
/// - **Mass:** kg, g, mg, lb, oz
/// - **Temperature:** C, F, K
///
/// @param value The numeric value to convert.
/// @param from  The source unit (e.g. "km", "lb", "F").
/// @param to    The target unit (e.g. "mi", "kg", "C").
/// @return The converted value.
/// @throws std::invalid_argument If the units are unknown or incompatible.
inline auto convert(double value, std::string_view from, std::string_view to)
  -> double {
  if (from == to) return value;

  if (detail::is_temperature_unit(from) && detail::is_temperature_unit(to)) {
    return detail::convert_temperature(value, from, to);
  }

  if (
    detail::find_factor(from, detail::length_to_meter) != nullptr &&
    detail::find_factor(to, detail::length_to_meter) != nullptr
  ) {
    return detail::convert_via_table(value, from, to, detail::length_to_meter);
  }

  if (
    detail::find_factor(from, detail::mass_to_kg) != nullptr &&
    detail::find_factor(to, detail::mass_to_kg) != nullptr
  ) {
    return detail::convert_via_table(value, from, to, detail::mass_to_kg);
  }

  throw std::invalid_argument(
    "Cannot convert between " + std::string(from) + " and " + std::string(to)
  );
}

}  // namespace convertunit
