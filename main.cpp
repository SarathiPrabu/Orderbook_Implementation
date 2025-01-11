#include "order_book.h"

int main() {
    OrderBook ob;

    ob.addOrder(1, 1001, Side::BUY, 100.5, 10);
    ob.addOrder(2, 1002, Side::SELL, 101.5, 5);
    ob.addOrder(3, 1003, Side::SELL, 100.5, 7);
    ob.addOrder(4, 1004, Side::BUY, 101, 8);
    
    ob.printOrderBook();
    return 0;
}
