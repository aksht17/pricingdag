#include <fstream>
#include <future>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <chrono>
#include "deltas.h"
#include "ingestion.h"
#include "option.h"
#include "tasknodes.h"

PricingResult runPricingDag(
    const OptionInput& option) {

    // Root node: calculate d1 asynchronously.
    auto d1Task = std::async(
        std::launch::async,
        [option] {
            return calculateD1(option);
        });

    // d1 has multiple consumers, so convert it to shared_future.
    std::shared_future<double> d1 = d1Task.share();

    // d2 depends on d1.
    auto d2Task = std::async(
        std::launch::async,
        [d1, option] {
            return calculateD2(d1.get(), option);
        });

    // Delta depends on d1.
    auto deltaTask = std::async(
        std::launch::async,
        [d1] {
            return calculateDelta(d1.get());
        });

    // Call price depends on both d1 and d2.
    auto priceTask = std::async(
        std::launch::async,
        [d1, d2 = d2Task.share(), option] {
            return calculateCallPrice(
                d1.get(),
                d2.get(),
                option);
        });

    // Wait for the terminal nodes.
    return {
        priceTask.get(),
        deltaTask.get()
    };
}

int main() {
    auto start = std::chrono::steady_clock::now();
    try {
        const std::vector<OptionInput> options =
            loadMarketData("market_data_real.csv");

        std::vector<std::future<PricingResult>> resultTasks;
        resultTasks.reserve(options.size());

        // Each option row is an independent DAG.
        for (const OptionInput& option : options) {
            resultTasks.push_back(
                std::async(
                    std::launch::async,
                    [option] {
                        return runPricingDag(option);
                    }));
        }

        std::ofstream output(
            "priced_options_output.csv");

        if (!output.is_open()) {
            std::cerr << "Could not open output file.\n";
            return 1;
        }

        output <<
            "Spot,Strike,Time,Rate,Volatility,"
            "CallPrice,Delta\n";

        for (std::size_t index = 0;
             index < options.size();
             ++index) {

            const PricingResult result =
                resultTasks[index].get();

            const OptionInput& option = options[index];

            output << option.spot << ","
                   << option.strike << ","
                   << option.time << ","
                   << option.rate << ","
                   << option.volatility << ","
                   << result.callPrice << ","
                   << result.delta << "\n";
        }

        std::cout
            << "DAG execution complete.\n"
            << "Processed "
            << options.size()
            << " options.\n"
            << "Output: priced_options_output.csv\n";
    }
    catch (const std::exception& error) {
        std::cerr << "Error: "
                  << error.what()
                  << "\n";
        return 1;
    }
    auto finish = std::chrono::steady_clock::now();

auto elapsed =
    std::chrono::duration_cast<std::chrono::microseconds>(
        finish - start);

std::cout << "Elapsed time: "
          << elapsed.count()
          << " microseconds\n";
    return 0;

    /*DAG execution complete.
Processed 482 options.
Output: priced_options_output.csv
Elapsed time: 25155 microseconds*/
}