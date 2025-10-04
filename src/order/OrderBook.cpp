#include "OrderBook.h"

#include <cassert>

void OrderBook::addOrder(std::unique_ptr<Order> order)
{
    if (order->getOrderType() == ORDER::BUY)
    {
        m_buyOrders->push(order);
    }
    else
    {
        m_sellOrders->push(order);
    };
}

void OrderBook::removeOrder(long long orderID) { (void)orderID; }

void OrderBook::fillOrder(std::unique_ptr<Order> o1, std::unique_ptr<Order> o2)
{
    cout << "Order1 ID: " << o1->getID() << "Order2 ID: " << o2->getID() << endl;
}

Order* OrderBook::peekBestBid() const
{
    if (!m_buyOrders || m_buyOrders->empty()) return nullptr;

    return m_buyOrders->top().get();
}

Order* OrderBook::peekBestAsk() const
{
    if (!m_sellOrders || m_sellOrders->empty()) return nullptr;

    return m_sellOrders->top().get();
}

void OrderBook::showOrders()
{
    assert(!m_buyOrders->empty() || !m_sellOrders->empty());

    for (; !m_buyOrders->empty(); m_buyOrders->pop())
    {
        m_buyOrders->top()->printDetails();
    }

    for (; !m_sellOrders->empty(); m_sellOrders->pop())
    {
        m_sellOrders->top()->printDetails();
    }
}
