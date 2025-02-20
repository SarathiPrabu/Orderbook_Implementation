#include "order_book.h"
#include <chrono>
#include <random>
#include <iostream>

void benchmarkOrderBook(int num_orders, int test_duration_seconds) {
    OrderBook ob;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> price_dist(95.0, 105.0);
    std::uniform_int_distribution<> qty_dist(1, 100);
    std::uniform_int_distribution<> side_dist(0, 1);

    auto start = std::chrono::high_resolution_clock::now();
    auto end_time = start + std::chrono::seconds(test_duration_seconds);

    int order_count = 0;

    while (std::chrono::high_resolution_clock::now() < end_time && order_count < num_orders) {
        Side side = (side_dist(gen) == 0) ? Side::BUY : Side::SELL;
        Price price = price_dist(gen);
        Qty qty = qty_dist(gen);

        ob.addOrder(order_count + 1, order_count + 1, side, price, qty);
        order_count++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    ob.printOrderBook();
    std::cout << "Processed " << order_count << " orders in " << elapsed.count() << " seconds\n";
    std::cout << "Orders per second: " << (order_count / elapsed.count()) << "\n";
}

int main() {
    constexpr int NUM_ORDERS = 1000000;  // Maximum orders to attempt
    constexpr int TEST_DURATION = 1;     // Run test for 1 second

    benchmarkOrderBook(NUM_ORDERS, TEST_DURATION);

    return 0;
}
