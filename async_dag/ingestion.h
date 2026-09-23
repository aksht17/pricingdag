#pragma once

#include <string>
#include <vector>

#include "option.h"

std::vector<OptionInput> loadMarketData(
    const std::string& filename);