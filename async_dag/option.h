#pragma once

struct OptionInput {
    double spot;
    double strike;
    double time;
    double rate;
    double volatility;
};

struct PricingResult {
    double callPrice;
    double delta;
};