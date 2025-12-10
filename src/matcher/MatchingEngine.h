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
    void sell();
    void buy();
    void fillOrder();

 private:
    std::shared_ptr<OrderBook> m_ob{};
    std::unique_ptr<Order>     m_currentOrder{};

    double currentPrice{};

    std::vector<Trade> completedTrades{};
};

#endif /* E525F97B_4F13_4C75_A01F_FD07567571E0 */
