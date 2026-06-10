#include "arithmeticoperations.h"

#include <cmath>
#include <limits>

namespace arithmetic {

double addNumbers(double a, double b)
{
    const double raw = a + b;

    if (std::isinf(raw) || raw > kMaxDouble) {
        return kMaxDouble;
    }
    if (raw < kMinDouble) {
        return kMinDouble;
    }
    return raw;
}

double subtractNumbers(double a, double b)
{
    const double rawDifference = a - b;

    if (std::isnan(rawDifference)) {
        return 0.0;
    }

    if (rawDifference == 0.0) {
        return 0.0;
    }

    if (std::fpclassify(rawDifference) == FP_SUBNORMAL) {
        return 0.0;
    }

    return rawDifference;
}

}
