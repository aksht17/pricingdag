#include "tasknodes.h"

#include <cmath>
#include <cstddef>
#include <vector>

namespace {
double standardNormalCDF(double value) {
    return 0.5 * std::erfc(-value / std::sqrt(2.0));
}
}

std::vector<double> calculateCallPrices(
    const std::vector<double>& spots,
    const std::vector<double>& strikes,
    const std::vector<double>& times,
    const std::vector<double>& rates,
    const std::vector<double>& volatilities) {

    std::vector<double> prices(spots.size());

    for (std::size_t index = 0; index < spots.size(); ++index) {
        double volatilitySqrtTime =
            volatilities[index] * std::sqrt(times[index]);

        double d1 =
            (std::log(spots[index] / strikes[index]) +
             (rates[index] +
              volatilities[index] * volatilities[index] / 2.0) *
                 times[index]) /
            volatilitySqrtTime;

        double d2 = d1 - volatilitySqrtTime;

        prices[index] =
            spots[index] * standardNormalCDF(d1) -
            strikes[index] *
                std::exp(-rates[index] * times[index]) *
                standardNormalCDF(d2);
    }

    return prices;
}