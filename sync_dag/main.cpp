// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
// Include the headers for the files you created
#include "ingestion.h"
#include "tasknodes.h"
#include "deltas.h"

int main() {
    auto start = std::chrono::steady_clock::now();
    // ---------------------------------------------------------
    // 1. INGESTION (Handled by ingestion.cpp)
    // ---------------------------------------------------------
    std::vector<double> S, K, T, r, sigma;
    
    // Call whatever function you wrote in ingestion.cpp to fill the vectors
    loadMarketData("market_data.csv", S, K, T, r, sigma); 


    // ---------------------------------------------------------
    // 2. DAG COMPUTATION (Handled by tasknodes.cpp & deltas.cpp)
    // ---------------------------------------------------------
    
    // You launch your async nodes here...
    // ...
    // ...

    // The manager waits for all threads to finish and collects the final data
    std::vector<double> final_prices = calculateCallPrices(S, K, T, r, sigma);

    std::vector<double> final_deltas = calculateDeltas(S, K, T, r, sigma);


    // ---------------------------------------------------------
    // 3. EXPORT TO CSV (PASTE THE CODE HERE)
    // ---------------------------------------------------------
    std::cout << "DAG Execution Complete. Writing results to file..." << std::endl;

    std::ofstream out_file("priced_options_output.csv");
    if (!out_file.is_open()) {
        std::cerr << "Error: Failed to open output file." << std::endl;
        return 1;
    }

    out_file << "Spot,Strike,Time,Rate,Volatility,CallPrice,Delta\n";

    // Write the results row by row
    size_t N = S.size();
    for (size_t i = 0; i < N; ++i) {
        out_file << S[i] << ","
                 << K[i] << ","
                 << T[i] << ","
                 << r[i] << ","
                 << sigma[i] << ","
                 << final_prices[i] << ","
                 << final_deltas[i] << "\n";
    }

    out_file.close();
    std::cout << "Successfully wrote " << N << " records to priced_options_output.csv" << std::endl;
    auto finish = std::chrono::steady_clock::now();

    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(
            finish - start);

    std::cout << "Elapsed time: "
            << elapsed.count()
            << " microseconds\n";

    /*DAG Execution Complete. Writing results to file...
Successfully wrote 482 records to priced_options_output.csv
Elapsed time: 1456 microseconds*/
    return 0;
}