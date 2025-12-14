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
    if (order.getSide() == Side::BUY)
    {
        buy(order);
    }
    else
    {
        sell(order);
    }
}

void MatchingEngine::sell(Order& incomingOrder)
{
    int incomingQty = incomingOrder.getQuantity();

    auto  bestBidIter  = m_ob->getBestBid();
    int   bestPrice    = bestBidIter->first;
    auto& restingOrder = bestBidIter->second.front();

    int restingOrderQty = restingOrder.getQuantity();

    while (incomingQty > 0)
    {
        if (restingOrderQty > incomingQty)
        {
            createTrade(incomingOrder, restingOrder, bestPrice, incomingQty);
            restingOrder.setQuantity(restingOrderQty - incomingQty);
            incomingQty = 0;
        }
        else if (incomingQty > restingOrderQty)
        {
            createTrade(incomingOrder, restingOrder, bestPrice, restingOrderQty);
            incomingOrder.setQuantity(incomingQty - restingOrderQty);

            if (m_ob->peekBestBid() != bestPrice)
            {
            }
        }
    }
}

void MatchingEngine::buy(Order& order) {}

void MatchingEngine::createTrade(const Order& o1, const Order& o2, const int price,
                                 const int quantity)
{
    m_completedTrades.emplace_back(Trade{o1.getID(), o2.getID(), price, quantity});
}
