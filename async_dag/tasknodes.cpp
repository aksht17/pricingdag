#include "tasknodes.h"

#include <cmath>

namespace {
double standardNormalCDF(double value) {
    return 0.5 * std::erfc(-value / std::sqrt(2.0));
}
}

double calculateD1(const OptionInput& option) {
    const double volatilitySqrtTime =
        option.volatility * std::sqrt(option.time);

    return (
        std::log(option.spot / option.strike) +
        (option.rate +
         option.volatility * option.volatility / 2.0) *
            option.time
    ) / volatilitySqrtTime;
}

double calculateD2(
    double d1,
    const OptionInput& option) {

    return d1 -
           option.volatility * std::sqrt(option.time);
}

double calculateCallPrice(
    double d1,
    double d2,
    const OptionInput& option) {

    return option.spot * standardNormalCDF(d1) -
           option.strike *
               std::exp(-option.rate * option.time) *
               standardNormalCDF(d2);
}