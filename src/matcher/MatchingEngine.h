#ifndef E525F97B_4F13_4C75_A01F_FD07567571E0
#define E525F97B_4F13_4C75_A01F_FD07567571E0

#include <deque>
#include <memory>
#include <vector>

#include "Order.h"
#include "OrderBook.h"

class MatchingEngine
{
 public:
    MatchingEngine(const std::shared_ptr<OrderBook>& orderBook)
        : m_ob{orderBook} {};

    void match(Order& order);

    void listTrades();

 private:
    void matchMarket(Order& order);
    void matchLimit(Order& order);
    void matchOnce(Order& order);

    bool priceCrosses(const Order& o, Price currentPrice);
    void setCurrentPrice(const Price price) { m_currentPrice = price; }

    void createTrade(const Order& o1, const Order& o2, const Price price, const Quantity quantity);

 private:
    std::shared_ptr<OrderBook> m_ob{};
    std::vector<Trade>         m_completedTrades{};

    // Added this to allow market orders to be added if other orders are currently being matched
    // or it cant yet be matched and is just waiting.
    std::deque<Order> m_marketQueue{};

    Price m_currentPrice{};
};

#endif /* E525F97B_4F13_4C75_A01F_FD07567571E0 */
