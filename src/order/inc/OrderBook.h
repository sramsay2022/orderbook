#ifndef DD464386_82F4_4916_9C97_26F8B65EC003
#define DD464386_82F4_4916_9C97_26F8B65EC003

#include <list>
#include <map>
#include <unordered_map>

#include "Order.h"
#include "Types.h"

class OrderBook
{
 public:
#ifdef UNIT_TEST
    // TODO test directly adding into orderbook for removeOrderTests
    explicit OrderBook(std::vector<Order>& orders)
    {
        for (auto& o : orders)
        {
            m_ask.at(o.getPrice());
        }
    };
#endif

    OrderBook() = default;

    void showOrders();

    void addOrder(Order order);
    void removeOrder(const ID id);

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
    std::map<Price, std::list<Order>> m_bid;
    std::map<Price, std::list<Order>> m_ask;

    struct OrderLocator
    {
        std::list<Order>::iterator iter;

        Price price;
        Side  side;
    };
    std::unordered_map<Price, OrderLocator> m_ledger;
};

#endif /* DD464386_82F4_4916_9C97_26F8B65EC003 */
