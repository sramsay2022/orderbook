#ifndef DD464386_82F4_4916_9C97_26F8B65EC003
#define DD464386_82F4_4916_9C97_26F8B65EC003

#include <cassert>
#include <list>
#include <map>
#include <unordered_map>

#include "Order.h"

class OrderBook
{
 public:
    OrderBook() = default;

    void addOrder(const Order& order);
    void removeOrder(long long id);

    // auto peekBestBid() const { return m_buyOrders.begin(); }
    // auto peekBestAsk() const { return m_sellOrders.begin(); }

    void showOrders();

 private:
    std::list<Order>& getBucket(int price, Side side);

 private:
    struct PriceLevel
    {
        std::list<Order> buys{};   // Best bid is last element rend()
        std::list<Order> sells{};  // Best ask is first element begin()
    };
    std::map<int, PriceLevel> m_priceLevels;

    struct OrderLocator
    {
        const int  price;
        const Side side;

        const std::list<Order>::iterator iter;
    };
    std::unordered_map<long long, OrderLocator> ledger;
};

#endif /* DD464386_82F4_4916_9C97_26F8B65EC003 */
