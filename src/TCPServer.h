#pragma once
#include <vector>
#include <string>
#include "OrderBook.h"
#include "FIXParser.h"

class TCPServer {
    OrderBook& book;

public:
    TCPServer(OrderBook& b) : book(b) {}

    void processMessages(const std::vector<std::string>& messages) {
        for (const auto& msg : messages) {
            Order o = parseFIX(msg);
            book.addOrder(o);
        }
    }
};