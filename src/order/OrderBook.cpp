#include "OrderBook.h"

#include <cassert>

#include "Order.h"

void OrderBook::addOrder(const Order& order)
{
    if (order.getSide() == Side::BUY)
    {
        m_priceLevels[order.getPrice()].buys.push_back(order);
    }
    else
    {
        m_priceLevels[order.getPrice()].sells.push_back(order);
    };
}

void OrderBook::removeBuyOrder(std::deque<Order>::iterator itr) {}

void OrderBook::showOrders()
{
    for (const auto& [price, ordersAtPrice] : m_priceLevels)
    {
        std::cout << "Bid price " << price << '\n';
        for (const auto& order : ordersAtPrice.buys)
        {
            order.printDetails();
        }
    }

    for (const auto& [price, ordersAtPrice] : m_priceLevels)
    {
        std::cout << "Ask price " << price << '\n';
        for (const auto& order : ordersAtPrice.sells)
        {
            order.printDetails();
        }
    }
}
