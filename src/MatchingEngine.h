#pragma once
#include "OrderBook.h"
#include "PnLTracker.h"
#include <string>

class MatchingEngine {
    OrderBook   book;
    PnLTracker  tracker;

public:
    void processOrder(const Order& o) {
        if (o.is_buy)
            tracker.recordBuy(o.price, o.quantity);
        else
            tracker.recordSell(o.price, o.quantity);
        
        book.addOrder(o);
    }

    void showPnL(double current_price) {
        tracker.printSummary(current_price);
    }

    OrderBook& getBook() {
        return book;
    }
};