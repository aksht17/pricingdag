#pragma once

#include "option.h"

double calculateD1(const OptionInput& option);

double calculateD2(
    double d1,
    const OptionInput& option);

double calculateCallPrice(
    double d1,
    double d2,
    const OptionInput& option);