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

void MatchingEngine::match(Order& incoming)
{
    incoming.isMarket() ? matchMarket(incoming) : matchLimit(incoming);
}

void MatchingEngine::matchMarket(Order& incoming)
{
    while (incoming.getQuantity() > 0)
    {
        if (m_ob->isOppositeEmpty(incoming.getSide()))
        {
            break;
        }
        matchOnce(incoming);
    }
}
void MatchingEngine::matchLimit(Order& incoming)
{
    while (incoming.getQuantity() > 0)
    {
        if (m_ob->isOppositeEmpty(incoming.getSide())) break;

        auto  bestPriceIter = m_ob->getOppositeBestPrice(incoming.getSide());
        Price bestOpPrice   = bestPriceIter->first;

        if (!priceCrosses(incoming, bestOpPrice))
        {
            break;
        }
        matchOnce(incoming);
    }

    if (!incoming.isFilled())
    {
        m_ob->addOrder(incoming);
    }
}

void MatchingEngine::matchOnce(Order& incoming)
{
    auto   bestPriceIter = m_ob->getOppositeBestPrice(incoming.getSide());
    Order& resting       = bestPriceIter->second.front();

    const Price    price       = bestPriceIter->first;
    const Quantity incomingQty = incoming.getQuantity();
    const Quantity restingQty  = resting.getQuantity();
    const Quantity takeQty     = std::min(incomingQty, restingQty);

    createTrade(incoming, resting, price, takeQty);
    setCurrentPrice(price);

    resting.reduceQuantity(takeQty);
    incoming.reduceQuantity(takeQty);

    if (resting.isFilled())
    {
        m_ob->removeOrder(resting.getID());
    }
}

bool MatchingEngine::priceCrosses(const Order& order, Price currentPrice)
{
    if (order.isBuy())
    {
        return order.getPrice() >= currentPrice;
    }
    else
    {  // Side::SELL
        return order.getPrice() <= currentPrice;
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
