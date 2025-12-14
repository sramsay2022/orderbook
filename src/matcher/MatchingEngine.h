#ifndef E525F97B_4F13_4C75_A01F_FD07567571E0
#define E525F97B_4F13_4C75_A01F_FD07567571E0

#include <__tree>
#include <list>
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
    void sell(Order& order);
    void buy(Order& order);
    void fillOrder();
    void createTrade(const Order& o1, const Order& o2, const int price, const int quantity);

    void setCurrentPrice(const int price) { m_currentPrice = price; }

    void resetToCurrentBucket();

    void listTrades();

 private:
    std::shared_ptr<OrderBook> m_ob{};
    std::vector<Trade>         m_completedTrades{};

    int m_currentPrice{};
};

#endif /* E525F97B_4F13_4C75_A01F_FD07567571E0 */
