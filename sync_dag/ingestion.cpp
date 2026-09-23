#include "ingestion.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

void loadMarketData(
    const std::string& filename,
    std::vector<double>& spots,
    std::vector<double>& strikes,
    std::vector<double>& times,
    std::vector<double>& rates,
    std::vector<double>& volatilities) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;

    // Skip the CSV header
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
            throw std::runtime_error("Invalid row in: " + filename);
        }

        spots.push_back(fields[0]);
        strikes.push_back(fields[1]);
        times.push_back(fields[2]);
        rates.push_back(fields[3]);
        volatilities.push_back(fields[4]);
    }
}