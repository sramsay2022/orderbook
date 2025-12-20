#include "OrderBook.h"

#include <cassert>

#include "Order.h"

void OrderBook::addOrder(const Order& order)
{
    const Price price = order.getPrice();
    const Side  side  = order.getSide();

    auto& book   = getBook(side);
    auto& bucket = book[price];
    bucket.push_back(order);

    auto iter = std::prev(bucket.end());
    ledger.emplace(order.getID(), OrderLocator{iter, price, side});
}

void OrderBook::removeOrder(const long long id)
{
    auto it = ledger.find(id);
    if (it == ledger.end()) return;

    auto& loc    = it->second;
    auto& book   = getBook(loc.side);
    auto& bucket = book[loc.price];

    // Erase the order in price bucket
    bucket.erase(loc.iter);

    // If no more orders in price bucket, erase the bucket
    if (bucket.empty())
    {
        book.erase(loc.price);
    }

    // Erase ledger entry
    ledger.erase(id);
}

void OrderBook::showOrders()
{
    for (const auto& [price, ordersAtPrice] : m_bid)
    {
        std::cout << "Bid price " << price << '\n';
        for (const auto& order : ordersAtPrice)
        {
            order.printDetails();
        }
    }

    for (const auto& [price, ordersAtPrice] : m_ask)
    {
        std::cout << "Ask price " << price << '\n';
        for (const auto& order : ordersAtPrice)
        {
            order.printDetails();
        }
    }
}
