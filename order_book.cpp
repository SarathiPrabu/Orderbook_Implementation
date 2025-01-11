#include "order_book.h"

// Add an order to the book
void OrderBook::addOrder(ClientId client_id, OrderId order_id, Side side, Price price, Qty qty) {
    if (side == Side::BUY) {
        if (buy_orders.find(price) == buy_orders.end()) {
            buy_orders[price] = PriceLevel{price, {}};
        }
        buy_orders[price].orders.emplace_back(order_id, client_id, side, price, qty);
        auto it = std::prev(buy_orders[price].orders.end());
        order_lookup[order_id] = {side, it};
    } else {
        if (sell_orders.find(price) == sell_orders.end()) {
            sell_orders[price] = PriceLevel{price, {}};
        }
        sell_orders[price].orders.emplace_back(order_id, client_id, side, price, qty);
        auto it = std::prev(sell_orders[price].orders.end());
        order_lookup[order_id] = {side, it};
    }

    matchOrders();
}

void OrderBook::cancelOrder(OrderId order_id) {
    if (order_lookup.find(order_id) == order_lookup.end()) return;

    auto [side, it] = order_lookup[order_id];

    if (side == Side::BUY) {
        auto price = it->price;
        buy_orders[price].orders.erase(it);
        if (buy_orders[price].orders.empty()) buy_orders.erase(price);
    } else {
        auto price = it->price;
        sell_orders[price].orders.erase(it);
        if (sell_orders[price].orders.empty()) sell_orders.erase(price);
    }

    order_lookup.erase(order_id);
}


// Match orders in the book
void OrderBook::matchOrders() {
    while (!buy_orders.empty() && !sell_orders.empty()) {
        auto buy_it = buy_orders.begin();
        auto sell_it = sell_orders.begin();

        if (buy_it->first < sell_it->first) break; // No match

        auto& buy_orders_list = buy_it->second.orders;
        auto& sell_orders_list = sell_it->second.orders;

        while (!buy_orders_list.empty() && !sell_orders_list.empty()) {
            auto& buy_order = buy_orders_list.front();
            auto& sell_order = sell_orders_list.front();

            Qty traded_qty = std::min(buy_order.qty, sell_order.qty);
            std::cout << "Trade executed: " << traded_qty << " @ " << sell_it->first << std::endl;

            buy_order.qty -= traded_qty;
            sell_order.qty -= traded_qty;

            if (buy_order.qty == 0) buy_orders_list.pop_front();
            if (sell_order.qty == 0) sell_orders_list.pop_front();
        }

        if (buy_orders_list.empty()) buy_orders.erase(buy_it);
        if (sell_orders_list.empty()) sell_orders.erase(sell_it);
    }
}

// Print the order book
void OrderBook::printOrderBook() const {
    std::cout << "Order Book:\n";
    std::cout << "BUY:\n";
    for (const auto& [price, level] : buy_orders) {
        for (const auto& order : level.orders) {
            std::cout << "Price: " << price << " Qty: " << order.qty << " [Order ID: " << order.order_id << "]\n";
        }
    }

    std::cout << "SELL:\n";
    for (const auto& [price, level] : sell_orders) {
        for (const auto& order : level.orders) {
            std::cout << "Price: " << price << " Qty: " << order.qty << " [Order ID: " << order.order_id << "]\n";
        }
    }
}
