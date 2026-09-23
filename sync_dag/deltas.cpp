#include "deltas.h"

#include <cmath>
#include <vector>

namespace {
constexpr double pi = 3.14159265358979323846;

double stnormCDF(double value) {
    return 0.5 * std::erfc(-value / std::sqrt(2.0));
}

double normPDF(double value) {
    return (1.0 / std::sqrt(2.0 * pi)) *
           std::exp(-0.5 * value * value);
}
}

std::vector<double> calculateDeltas(
    const std::vector<double>& spots,
    const std::vector<double>& strikes,
    const std::vector<double>& times,
    const std::vector<double>& rates,
    const std::vector<double>& volatilities) {

    std::vector<double> deltas(spots.size());

    for (std::size_t index = 0; index < spots.size(); ++index) {
        double volatilitySqrtTime =
            volatilities[index] * std::sqrt(times[index]);

        double d1 =
            (std::log(spots[index] / strikes[index]) +
             (rates[index] +
              volatilities[index] * volatilities[index] / 2.0) *
                 times[index]) /
            volatilitySqrtTime;

        deltas[index] = stnormCDF(d1);
    }

    return deltas;
}