#include "MatchingEngine.h"

#include <memory>
#include <utility>

#include "Order.h"

/* Logic:
    Market order in:
    -> match immedietly with top result
    ->repeat until order filled
    -> if bucket empty add to orderbook (Needs priority over limit orders)

    Limit Order in:
    -> check to see if price of top is more/less
    -> add to queue if other orders come before

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

        const Price    price       = bestPriceIter->first;
        const Quantity incomingQty = incoming.getQuantity();
        const Quantity restingQty  = resting.getQuantity();
        const Quantity takeQty     = std::min(incomingQty, restingQty);

        createTrade(incoming, resting, price, takeQty);

        resting.reduceQuantity(takeQty);
        incoming.reduceQuantity(takeQty);

        if (resting.isFilled())
        {
            m_ob->removeOrder(resting.getID());
            setCurrentPrice(price);
        }
    }
}

void MatchingEngine::createTrade(const Order& o1, const Order& o2, const Price price,
                                 const Quantity quantity)
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
