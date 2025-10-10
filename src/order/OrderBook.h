#ifndef DD464386_82F4_4916_9C97_26F8B65EC003
#define DD464386_82F4_4916_9C97_26F8B65EC003

#include <cassert>

#include "Order.h"

class OrderBook
{
 public:
    OrderBook() = default;

    void addOrder(const Order& order);
    void removeBuyOrder(std::deque<Order>::iterator itr);
    void removeSellOrder(std::deque<Order>::iterator itr);

    // auto peekBestBid() const { return m_buyOrders.begin(); }
    // auto peekBestAsk() const { return m_sellOrders.begin(); }

    // void removeBid(OrderBookSet::iterator it) { m_buyOrders.erase(it); }
    // void removeAsk(OrderBookSet::iterator it) { m_sellOrders.erase(it); }

    void showOrders();

 private:
    struct PriceLevel
    {
        std::deque<Order> buys{};   // Best bid is last element
        std::deque<Order> sells{};  // Best ask is first element
    };
    // Both buys and sells are sorted using std::less
    std::map<int, PriceLevel> m_priceLevels;

    //<ID, <price, iterator>> maps an iterator to the order that contains the orderID
    std::unordered_map<long long, std::pair<double, std::deque<Order>::iterator>> ledger;
};

#endif /* DD464386_82F4_4916_9C97_26F8B65EC003 */
