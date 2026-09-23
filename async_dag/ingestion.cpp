#include "ingestion.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<OptionInput> loadMarketData(
    const std::string& filename) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(
            "Could not open file: " + filename);
    }

    std::vector<OptionInput> options;
    std::string line;

    // Skip the CSV header.
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream row(line);
        std::string value;
        std::vector<double> fields;

        while (std::getline(row, value, ',')) {
            fields.push_back(std::stod(value));
        }

        if (fields.size() != 5) {
            throw std::runtime_error(
                "Invalid row in: " + filename);
        }

        options.push_back({
            fields[0], // Spot
            fields[1], // Strike
            fields[2], // Time
            fields[3], // Rate
            fields[4]  // Volatility
        });
    }

    return options;
}