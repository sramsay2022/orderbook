#include "MatchingEngine.h"

#include <memory>
#include <utility>

#include "Order.h"

/* Logic:
    Order in -> Check if Market -> match immedietly with top result
    Order in -> Check if Limit -> check to see if price of top is more/less -> add to queue if
    other orders come before

    -> fill order if only one at that price and matchs top oppposite

*/

// Market orders, price is not checked, orders are filled automatically
void MatchingEngine::match(Order& order)
{
    if (order.getType() == OrderType::MARKET)
    {
        matchMarket(order);
    }
}

void MatchingEngine::matchMarket(Order& incoming)
{
    while (incoming.getQuantity() > 0)
    {
        if (m_ob->isOppositeEmpty(incoming.getSide()))
        {
            m_ob->addOrder(incoming);
            return;
        }
        // getBestPrice returns opposite book
        auto   bestPriceIter = m_ob->getOppositeBestPrice(incoming.getSide());
        Order& resting       = bestPriceIter->second.front();

        const int price        = bestPriceIter->first;
        const int incomingQty  = incoming.getQuantity();
        const int restingQty   = resting.getQuantity();
        const int takeQuantity = std::min(incomingQty, restingQty);

        createTrade(incoming, resting, price, takeQuantity);

        resting.reduceQuantity(takeQuantity);
        incoming.reduceQuantity(takeQuantity);

        if (resting.isFilled())
        {
            m_ob->removeOrder(resting.getID());
            setCurrentPrice(price);
        }
    }
}

void MatchingEngine::resetToCurrentBucket() {}

void MatchingEngine::createTrade(const Order& o1, const Order& o2, const int price,
                                 const int quantity)
{
    m_completedTrades.emplace_back(Trade{o1.getID(), o2.getID(), price, quantity});
}

void MatchingEngine::listTrades()
{
    for (auto& t : m_completedTrades)
    {
        t.printDetails();
    }
}
