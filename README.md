# Order Book Implementation 🚀

A high-performance C++ order book designed for fast and efficient order matching in a trading system.

## Features
- Supports **limit orders** (buy/sell) with price-time priority.
- Efficient **order matching engine** with real-time execution.
- Uses **hash maps and linked lists** for optimized order management.
- Implements **order cancellation** and market updates.

## Installation & Compilation
```bash
g++ -std=c++23 -O2 -Wall -Wextra order_book.cpp main.cpp -o order_book
```

## Usage
Run the executable:
```bash
./order_book
```

## Example Output
```
Trade executed: 5 @ 99.5
Trade executed: 7 @ 100.5
Order Book:
BUY:
Price: 101 Qty: 8 [Order ID: 1004]
Price: 100.5 Qty: 3 [Order ID: 1001]
SELL:
(empty)
```

## Future Improvements
- Add **multi-threading** for handling high-frequency trading.
- Support **market orders** and **stop-loss orders**.
- Integrate **WebSockets** for real-time market data updates.

---

### 📌 Author
**Sarathi Prabu**  
GitHub: [Orderbook_Implementation](https://github.com/SarathiPrabu/Orderbook_Implementation)

---
Feel free to contribute or suggest improvements! 🚀
