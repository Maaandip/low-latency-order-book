#include "FIXParser.h"
#include <iostream>

void processMessage(const std::string& msg, OrderBook& book) {
    try {
        Order o = parseFIX(msg);
        book.addOrder(o);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing message: " << e.what() << "\n";
    }
}