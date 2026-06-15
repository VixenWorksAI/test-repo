#include "arithmeticoperations.h"

#include <cmath>
#include <limits>

#if defined(__GNUC__) || defined(__clang__)
#define AO_UNLIKELY(x) __builtin_expect(!!(x), 0)
#define AO_LIKELY(x)   __builtin_expect(!!(x), 1)
#else
#define AO_UNLIKELY(x) (x)
#define AO_LIKELY(x)   (x)
#endif

namespace arithmetic {

double addNumbers(double a, double b) noexcept
{
    double raw = a + b;

    if (AO_UNLIKELY(__builtin_isinf(raw) || raw > kMaxDouble)) {
        return kMaxDouble;
    }
    if (AO_UNLIKELY(raw < kMinDouble)) {
        return kMinDouble;
    }
    return raw;
}

double subtractNumbers(double a, double b) noexcept
{
    double rawDifference = a - b;

    if (AO_UNLIKELY(__builtin_isnan(rawDifference))) {
        return 0.0;
    }
    if (AO_UNLIKELY(rawDifference == 0.0)) {
        return 0.0;
    }
    if (AO_UNLIKELY(__builtin_fpclassify(FP_SUBNORMAL, FP_NORMAL, FP_NORMAL, FP_NORMAL, FP_NORMAL, rawDifference) == FP_SUBNORMAL)) {
        return 0.0;
    }
    return rawDifference;
}

double multiplyNumbers(double a, double b) noexcept
{
    double rawProduct = a * b;

    if (AO_UNLIKELY(__builtin_isnan(rawProduct))) {
        return 0.0;
    }
    if (AO_UNLIKELY(__builtin_isinf(rawProduct))) {
        return (a > 0.0) == (b > 0.0) ? kMaxDouble : kMinDouble;
    }
    if (AO_UNLIKELY(rawProduct > kMaxDouble)) {
        return kMaxDouble;
    }
    if (AO_UNLIKELY(rawProduct < kMinDouble)) {
        return kMinDouble;
    }
    return rawProduct;
}

double divideNumbers(double a, double b) noexcept
{
    if (AO_UNLIKELY(b == 0.0)) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return a / b;
}

}
