#pragma once

#include <vector>

std::vector<double> calculateDeltas(
    const std::vector<double>& spots,
    const std::vector<double>& strikes,
    const std::vector<double>& times,
    const std::vector<double>& rates,
    const std::vector<double>& volatilities);