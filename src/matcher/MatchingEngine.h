#ifndef E525F97B_4F13_4C75_A01F_FD07567571E0
#define E525F97B_4F13_4C75_A01F_FD07567571E0

#include "Order.h"
#include "OrderBook.h"

class MatchingEngine
{
 public:
    MatchingEngine(const std::shared_ptr<OrderBook>& orderBook)
        : m_ob{orderBook} {};

    void match(std::unique_ptr<Order> order);

 private:
    std::shared_ptr<OrderBook> m_ob;
};

#endif /* E525F97B_4F13_4C75_A01F_FD07567571E0 */
