#ifndef DD464386_82F4_4916_9C97_26F8B65EC003
#define DD464386_82F4_4916_9C97_26F8B65EC003

#include <cassert>
#include <memory>
#include <set>

#include "Order.h"

// Compare the for the lowest price then compare for earliest time if at same price. FIFO
struct OrderPtrCmp
{
    bool operator()(const std::unique_ptr<Order>& o1, const std::unique_ptr<Order>& o2) const
    {
        assert(o1 && o2);
        if (o1->getPrice() == o2->getPrice())
        {
            return o1->getTime() < o2->getTime();
        }
        return o1->getPrice() < o2->getPrice();
    }
};

using OrderBookSet = std::set<std::unique_ptr<Order>, OrderPtrCmp>;

class OrderBook
{
 public:
    OrderBook() = default;

    void addOrder(std::unique_ptr<Order> order);
    void removeOrder(long long orderID);

    auto peekBestBid() const { return m_buyOrders.begin(); }
    auto peekBestAsk() const { return m_sellOrders.begin(); }

    void removeBid(OrderBookSet::iterator it) { m_buyOrders.erase(it); }
    void removeAsk(OrderBookSet::iterator it) { m_sellOrders.erase(it); }

    void showOrders();

 private:
    OrderBookSet m_buyOrders{};
    OrderBookSet m_sellOrders{};

    std::map<Order, Order> filledOrders{};  // TODO
};

#endif /* DD464386_82F4_4916_9C97_26F8B65EC003 */
