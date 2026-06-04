#pragma once
#include <iostream>
#include <unordered_map>
#include "OrderBook.h"

class PnLTracker {
    double realized_pnl = 0.0;
    double total_bought = 0.0;
    double total_sold   = 0.0;
    int    qty_bought   = 0;
    int    qty_sold     = 0;

public:
    void recordBuy(double price, int qty) {
        total_bought += price * qty;
        qty_bought   += qty;
    }

    void recordSell(double price, int qty) {
        total_sold += price * qty;
        qty_sold   += qty;
    }

    double getUnrealizedPnL(double current_price) {
        int net_qty = qty_bought - qty_sold;
        return (current_price * net_qty) - (total_bought - total_sold);
    }

    double getRealizedPnL() {
        return total_sold - total_bought;
    }

    void printSummary(double current_price) {
        std::cout << "=== PnL Summary ===\n";
        std::cout << "Realized PnL:   " << getRealizedPnL() << "\n";
        std::cout << "Unrealized PnL: " << getUnrealizedPnL(current_price) << "\n";
        std::cout << "Total Bought:   " << qty_bought << " units\n";
        std::cout << "Total Sold:     " << qty_sold   << " units\n";
    }
};