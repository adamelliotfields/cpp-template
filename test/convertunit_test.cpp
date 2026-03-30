#include "convertunit.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using Catch::Matchers::WithinAbs;
using convertunit::convert;

// Length

TEST_CASE("Kilometers to meters") {
  CHECK_THAT(convert(1.0, "km", "m"), WithinAbs(1000.0, 1e-9));
}

TEST_CASE("Miles to kilometers") {
  CHECK_THAT(convert(1.0, "mi", "km"), WithinAbs(1.609344, 1e-6));
}

TEST_CASE("Feet to inches") {
  CHECK_THAT(convert(1.0, "ft", "in"), WithinAbs(12.0, 1e-9));
}

TEST_CASE("Yards to feet") {
  CHECK_THAT(convert(1.0, "yd", "ft"), WithinAbs(3.0, 1e-9));
}

TEST_CASE("Centimeters to inches") {
  CHECK_THAT(convert(2.54, "cm", "in"), WithinAbs(1.0, 1e-9));
}

// Mass

TEST_CASE("Kilograms to grams") {
  CHECK_THAT(convert(1.0, "kg", "g"), WithinAbs(1000.0, 1e-9));
}

TEST_CASE("Pounds to kilograms") {
  CHECK_THAT(convert(1.0, "lb", "kg"), WithinAbs(0.45359237, 1e-9));
}

TEST_CASE("Ounces to grams") {
  CHECK_THAT(convert(1.0, "oz", "g"), WithinAbs(28.349523125, 1e-9));
}

TEST_CASE("Pounds to ounces") {
  CHECK_THAT(convert(1.0, "lb", "oz"), WithinAbs(16.0, 1e-6));
}

// Temperature

TEST_CASE("Celsius to Fahrenheit") {
  CHECK_THAT(convert(0.0, "C", "F"), WithinAbs(32.0, 1e-9));
  CHECK_THAT(convert(100.0, "C", "F"), WithinAbs(212.0, 1e-9));
}

TEST_CASE("Fahrenheit to Celsius") {
  CHECK_THAT(convert(32.0, "F", "C"), WithinAbs(0.0, 1e-9));
  CHECK_THAT(convert(212.0, "F", "C"), WithinAbs(100.0, 1e-9));
}

TEST_CASE("Celsius to Kelvin") {
  CHECK_THAT(convert(0.0, "C", "K"), WithinAbs(273.15, 1e-9));
  CHECK_THAT(convert(100.0, "C", "K"), WithinAbs(373.15, 1e-9));
}

TEST_CASE("Kelvin to Celsius") {
  CHECK_THAT(convert(273.15, "K", "C"), WithinAbs(0.0, 1e-9));
}

TEST_CASE("Fahrenheit to Kelvin") {
  CHECK_THAT(convert(32.0, "F", "K"), WithinAbs(273.15, 1e-9));
}

// Identity

TEST_CASE("Same unit returns same value") {
  CHECK_THAT(convert(42.0, "m", "m"), WithinAbs(42.0, 1e-9));
  CHECK_THAT(convert(98.6, "F", "F"), WithinAbs(98.6, 1e-9));
}

// Error

TEST_CASE("Incompatible units throw") {
  CHECK_THROWS_AS(convert(1.0, "kg", "m"), std::invalid_argument);
  CHECK_THROWS_AS(convert(1.0, "C", "kg"), std::invalid_argument);
}
