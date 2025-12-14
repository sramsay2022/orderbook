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
    int peekBestBid() const { return std::prev(m_bid.end())->first; }
    int peekBestAsk() const { return m_ask.begin()->first; }

    bool isBidEmpty() const { return m_bid.empty(); }
    bool isAskEmpty() const { return m_ask.empty(); }

    auto getBestBid() { return std::prev(m_bid.end()); }
    auto getBestAsk() { return m_ask.begin(); }

    // This is for an order of one side to return the other side for matching
    auto getOppositeBestPrice(Side side)
    {
        return (side == Side::BUY) ? m_ask.begin() : std::prev(m_bid.end());
    }

    bool isOppositeEmpty(Side side) const
    {
        return (side == Side::BUY) ? m_ask.empty() : m_bid.empty();
    }

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
