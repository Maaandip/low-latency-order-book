#pragma once
#include "OrderBook.h"
#include <string>
#include <sstream>

// Parses messages like: "BUY 100 50.25" or "SELL 200 49.75"
inline Order parseFIX(const std::string& msg) {
    std::istringstream ss(msg);
    std::string side;
    int qty; 
    double price;
    ss >> side >> qty >> price;

    Order o;
    o.id       = nextOrderId();
    o.quantity = qty;
    o.price    = price;
    o.is_buy   = (side == "BUY");
    o.timestamp = 0;
    return o;
}