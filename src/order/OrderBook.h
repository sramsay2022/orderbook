#ifndef DD464386_82F4_4916_9C97_26F8B65EC003
#define DD464386_82F4_4916_9C97_26F8B65EC003

#include <cassert>
#include <memory>
#include <queue>
#include <vector>

#include "Order.h"

// Compare the for the lowest price then compare for earliest time. FIFO
struct OrderPtrCmp
{
    bool operator()(const std::unique_ptr<Order> o1, const std::unique_ptr<Order> o2) const
    {
        assert(o1 && o2);
        if (o1->getPrice() == o2->getPrice())
        {
            return o1->getTime() > o2->getTime();
        }
        return o1->getPrice() > o2->getPrice();
    }
};

using OrderBookQueue =
    std::priority_queue<std::unique_ptr<Order>, std::vector<std::unique_ptr<Order>>, OrderPtrCmp>;

class OrderBook
{
 public:
    OrderBook() = default;

    void addOrder(std::unique_ptr<Order> order);
    void removeOrder(long long orderID);
    void fillOrder(std::unique_ptr<Order> o1, std::unique_ptr<Order> o2);

    Order* peekBestBid() const;
    Order* peekBestAsk() const;

    void showOrders();

 private:
    std::shared_ptr<OrderBookQueue> m_buyOrders{std::make_shared<OrderBookQueue>()};
    std::shared_ptr<OrderBookQueue> m_sellOrders{std::make_shared<OrderBookQueue>()};

    std::map<Order, Order> filledOrders{};
};

#endif /* DD464386_82F4_4916_9C97_26F8B65EC003 */
