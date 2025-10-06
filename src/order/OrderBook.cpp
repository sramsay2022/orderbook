#include "OrderBook.h"

#include <cassert>

void OrderBook::addOrder(std::unique_ptr<Order> order)
{
    if (order->getSide() == Side::BUY)
    {
        m_buyOrders.insert(std::move(order));
    }
    else
    {
        m_sellOrders.insert(std::move(order));
    };
}

void OrderBook::removeOrder(long long orderID) { (void)orderID; }

void OrderBook::showOrders()
{
    assert(!m_buyOrders.empty());

    auto iterBuy = m_buyOrders.begin();

    for (; iterBuy != m_buyOrders.end(); iterBuy++)
    {
        iterBuy->get()->printDetails();
    }

    assert(!m_sellOrders.empty());

    auto iterSell = m_sellOrders.begin();
    for (; iterSell != m_sellOrders.end(); iterSell++)
    {
        iterSell->get()->printDetails();
    }
}
