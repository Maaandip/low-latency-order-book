#pragma once
#include <map>
#include <queue>
#include <cstdint>
#include <atomic>

struct Order {
    uint64_t id;
    double   price;
    int      quantity;
    bool     is_buy;
    uint64_t timestamp;
};

inline uint64_t nextOrderId() {
    static std::atomic<uint64_t> counter{1};
    return counter.fetch_add(1, std::memory_order_relaxed);
}

class OrderBook {
public:
    void addOrder(const Order& o);
    void cancelOrder(uint64_t id);
    void match();

private:
    std::map<double, std::queue<Order>, std::greater<double>> bids;
    std::map<double, std::queue<Order>> asks;
};