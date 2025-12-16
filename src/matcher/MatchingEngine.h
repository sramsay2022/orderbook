#ifndef E525F97B_4F13_4C75_A01F_FD07567571E0
#define E525F97B_4F13_4C75_A01F_FD07567571E0

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
    void matchMarket(Order& order);
    void matchLimit(Order& order);
    void fillOrder();

    void setCurrentPrice(const Price price) { m_currentPrice = price; }

    void createTrade(const Order& o1, const Order& o2, const Price price, const Quantity quantity);
    void listTrades();

 private:
    std::shared_ptr<OrderBook> m_ob{};
    std::vector<Trade>         m_completedTrades{};

    Price m_currentPrice{};
};

#endif /* E525F97B_4F13_4C75_A01F_FD07567571E0 */
