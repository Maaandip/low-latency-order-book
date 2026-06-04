#include "OrderBook.h"
#include <iostream>

void OrderBook::addOrder(const Order& o) {
    if (o.is_buy)
        bids[o.price].push(o);
    else
        asks[o.price].push(o);
    match();
}

void OrderBook::cancelOrder(uint64_t id) {
    // Future implementation
}

void OrderBook::match() {
    while (!bids.empty() && !asks.empty()) {
        auto& [bid_price, bid_queue] = *bids.begin();
        auto& [ask_price, ask_queue] = *asks.begin();

        if (bid_price < ask_price) break;

        Order& bid = bid_queue.front();
        Order& ask = ask_queue.front();

        int qty = std::min(bid.quantity, ask.quantity);
        std::cout << "MATCH: " << qty << " @ " << ask_price << "\n";

        bid.quantity -= qty;
        ask.quantity -= qty;

        if (bid.quantity == 0) { 
            bid_queue.pop(); 
            if (bid_queue.empty()) bids.erase(bid_price); 
        }
        if (ask.quantity == 0) { 
            ask_queue.pop(); 
            if (ask_queue.empty()) asks.erase(ask_price); 
        }
    }
}