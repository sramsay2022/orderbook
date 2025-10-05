#include "OrderBook.h"

#include <cassert>

void OrderBook::addOrder(std::unique_ptr<Order> order)
{
    if (order->getSide() == Side::BUY)
    {
        m_buyOrders->insert(std::move(order));
    }
    else
    {
        m_sellOrders->insert(std::move(order));
    };
}

void OrderBook::removeOrder(long long orderID) { (void)orderID; }

void OrderBook::fillOrder(std::unique_ptr<Order> o1)
{
    cout << "Order1 ID: " << o1->getID() << "Order2 ID: " << o1->getID() << endl;
}

Order* OrderBook::peekBestBid() const
{
    if (!m_buyOrders || m_buyOrders->empty()) return nullptr;

    return nullptr;
}

Order* OrderBook::peekBestAsk() const
{
    if (!m_sellOrders || m_sellOrders->empty()) return nullptr;

    return nullptr;
}

void OrderBook::showOrders()
{
    assert(!m_buyOrders->empty() || !m_sellOrders->empty());

    auto iterBuy  = m_buyOrders->begin();
    auto iterSell = m_sellOrders->begin();

    for (; iterBuy != m_buyOrders->end(); iterBuy++)
    {
        iterBuy->get()->printDetails();
    }

    for (; iterSell != m_sellOrders->end(); iterSell++)
    {
        iterSell->get()->printDetails();
    }
}
