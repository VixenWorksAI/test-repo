#ifndef ARITHMETICOPERATIONS_H
#define ARITHMETICOPERATIONS_H

#include <limits>

namespace arithmetic {

inline constexpr double kMaxDouble = 1.7976931348623157e308;
inline constexpr double kMinDouble = -1.7976931348623157e308;

double addNumbers(double a, double b) noexcept;

double subtractNumbers(double a, double b) noexcept;

double multiplyNumbers(double a, double b) noexcept;

double divideNumbers(double a, double b) noexcept;

}

#endif
