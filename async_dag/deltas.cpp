#include "deltas.h"

#include <cmath>

namespace {
constexpr double pi = 3.14159265358979323846;

double standardNormalCDF(double value) {
    return 0.5 * std::erfc(-value / std::sqrt(2.0));
}
}

double calculateDelta(double d1) {
    return standardNormalCDF(d1);
}