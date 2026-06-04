#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include "OrderBook.h"
#include "MatchingEngine.h"
#include "FIXParser.h"
#include "TCPServer.h"

int main() {
    std::cout << "=== Low-Latency Order Book Simulator ===\n\n";

    MatchingEngine engine;

    // Simulate FIX messages
    std::vector<std::string> messages = {
        "BUY 100 50.25",
        "SELL 100 50.25",
        "BUY 200 49.75",
        "SELL 150 49.75",
        "BUY 300 51.00",
        "SELL 300 51.00"
    };

    std::cout << "=== Processing Orders ===\n";
    for (const auto& msg : messages) {
        Order o = parseFIX(msg);
        engine.processOrder(o);
    }

    // Benchmark 1M orders
    std::cout << "\n=== Benchmark: 1M Orders ===\n";
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 500000; i++) {
        Order buy  = {nextOrderId(), 100.0 + (i % 5), 10, true,  0};
        Order sell = {nextOrderId(), 100.0 + (i % 5), 10, false, 0};
        engine.processOrder(buy);
        engine.processOrder(sell);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto ms  = std::chrono::duration_cast
                <std::chrono::milliseconds>(end - start).count();

    std::cout << "Processed 1M orders in " << ms << "ms\n";
    std::cout << "Throughput: " << (1000000.0 / ms) * 1000 << " orders/sec\n";

    // PnL Summary
    std::cout << "\n";
    engine.showPnL(50.50);

    return 0;
}