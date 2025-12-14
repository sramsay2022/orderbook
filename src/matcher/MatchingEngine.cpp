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
void MatchingEngine::match(const Order& order)
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

void MatchingEngine::sell(const Order& incomingOrder)
{
    int incomingQty = incomingOrder.getQuantity();

    while (incomingQty > 0)
    {
        auto bestBidIt = m_ob->getBestBid();

        int   bestPrice   = bestBidIt->first;
        auto& bestBidList = bestBidIt->second;

        auto& restingOrder    = bestBidList.front();
        int   limitOrderQuant = restingOrder.getQuantity();

        if (limitOrderQuant > incomingQty)
        {
            createTrade(incomingOrder, restingOrder, bestPrice, incomingQty);
            restingOrder.setQuantity(limitOrderQuant - incomingQty);
            incomingQty = 0;
        }
        else if (incomingQty > limitOrderQuant)
        {
        }
    }
}

void MatchingEngine::buy(const Order& order) {}

void MatchingEngine::createTrade(const Order& o1, const Order& o2, const int price,
                                 const int quantity)
{
    m_completedTrades.emplace_back(Trade{o1.getID(), o2.getID(), price, quantity});
}
