#include "OrderBook.h"

#include "Order.h"
#include "Types.h"

void OrderBook::addOrder(Order order)
{
    const ID    id    = order.getID();
    const Price price = order.getPrice();
    const Side  side  = order.getSide();

    auto& book   = getBook(side);
    auto& bucket = book.at(price);
    bucket.push_back(std::move(order));

    auto iter = std::prev(bucket.end());
    m_ledger.emplace(id, OrderLocator{iter, price, side});
}

void OrderBook::removeOrder(const ID id)
{
    auto it = m_ledger.find(id);
    if (it == m_ledger.end()) return;

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
    m_ledger.erase(id);
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
