#include "OrderBook.h"

#include <cassert>
#include <utility>

#include "Order.h"

void OrderBook::addOrder(const Order& order)
{
    const int  price = order.getPrice();
    const Side side  = order.getSide();

    auto& bucket = getBucket(price, side);

    bucket.emplace_back(order);
    auto iter = std::prev(bucket.end());

    ledger.emplace(order.getID(), OrderLocator{price, side, iter});
}

void OrderBook::removeOrder(long long id)
{
    auto& loc    = ledger.at(id);
    auto& bucket = getBucket(loc.price, loc.side);

    bucket.erase(loc.iter);
    ledger.erase(id);
}

std::list<Order>& OrderBook::getBucket(int price, Side side)
{
    auto& level = m_priceLevels[price];
    return (side == Side::BUY) ? level.buys : level.sells;
}

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
