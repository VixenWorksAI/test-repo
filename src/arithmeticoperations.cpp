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

}
