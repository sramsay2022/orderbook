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

    void match(const Order& order);
    void sell(const Order& order);
    void buy(const Order& order);
    void fillOrder();
    void createTrade(const Order& o1, const Order& o2, const int price, const int quantity);

 private:
    std::shared_ptr<OrderBook> m_ob{};

    double m_currentPrice{};

    std::vector<Trade> m_completedTrades{};
};

#endif /* E525F97B_4F13_4C75_A01F_FD07567571E0 */
