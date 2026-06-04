#include <iostream>
#include <string>
#include <sstream>
#include "OrderBook.h"
#include "FIXParser.h"

// Simulated TCP Server - processes orders from a message queue
class TCPServer {
    OrderBook& book;

public:
    TCPServer(OrderBook& b) : book(b) {}

    void processMessages(const std::vector<std::string>& messages) {
        std::cout << "=== TCP Server Started ===\n";
        std::cout << "Processing " << messages.size() << " messages...\n\n";
        
        for (const auto& msg : messages) {
            std::cout << "Received: " << msg << "\n";
            Order o = parseFIX(msg);
            book.addOrder(o);
        }

        std::cout << "\n=== TCP Server Done ===\n";
    }
};