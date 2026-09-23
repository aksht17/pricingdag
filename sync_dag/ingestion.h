#pragma once

#include <string>
#include <vector>

void loadMarketData(
    const std::string& filename,
    std::vector<double>& spots,
    std::vector<double>& strikes,
    std::vector<double>& times,
    std::vector<double>& rates,
    std::vector<double>& volatilities);