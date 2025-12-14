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

    void showOrders();

    void addOrder(const Order& order);
    void removeOrder(const long long id);

    auto& getBook(const Side side) { return (side == Side::BUY) ? m_bid : m_ask; }

    // BestBid: Lowest price someone will buy for - smallest value in map rbegin()
    // BestAsk: Highest price someone will sell for - largest value in map begin()
    int peekBestBid() const { return m_bid.rbegin()->first; }
    int peekBestAsk() const { return m_ask.begin()->first; }

    auto getBestBid() { return m_bid.rbegin(); }
    auto getBestAsk() { return m_bid.begin(); }

 private:
    std::map<int, std::list<Order>> m_bid;
    std::map<int, std::list<Order>> m_ask;

    struct OrderLocator
    {
        int  price;
        Side side;

        std::list<Order>::iterator iter;
    };
    std::unordered_map<long long, OrderLocator> ledger;
};

#endif /* DD464386_82F4_4916_9C97_26F8B65EC003 */
