#pragma once

#include <iostream>
#include <unordered_map>
#include <map>
#include <list>
#include <vector>
#include <memory>

using Price = double;
using Qty = uint64_t;
using OrderId = uint64_t;
using ClientId = uint64_t;
enum class Side { BUY, SELL };

struct Order {
    OrderId order_id;
    ClientId client_id;
    Side side;
    Price price;
    Qty qty;
    std::list<Order>::iterator iterator;  // Position in price level's order list

    Order(OrderId oid, ClientId cid, Side s, Price p, Qty q) 
        : order_id(oid), client_id(cid), side(s), price(p), qty(q) {}
};

struct PriceLevel {
    Price price;
    std::list<Order> orders;
};

class OrderBook {
public:
    void addOrder(ClientId client_id, OrderId order_id, Side side, Price price, Qty qty);
    void cancelOrder(OrderId order_id);
    void matchOrders();
    void printOrderBook() const;

private:
    std::map<Price, PriceLevel, std::greater<>> buy_orders;  // Highest price first
    std::map<Price, PriceLevel, std::less<>> sell_orders;    // Lowest price first
    std::unordered_map<OrderId, std::pair<Side, std::list<Order>::iterator>> order_lookup;
};
