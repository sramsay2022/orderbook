#include "MatchingEngine.h"

#include <memory>

#include "Order.h"

/* Logic:
    Order in -> Check if Market -> match immedietly with top result
    Order in -> Check if Limit -> check to see if price of top is more/less -> add to queue if other
   orders come before

                                                                            -> fill order if only
   one at that price and matchs top oppposite

*/

// Market orders, price is not checked, orders are filled automatically
void MatchingEngine::match(std::unique_ptr<Order> order)
{
    m_currentOrder = std::move(order);

    if (m_currentOrder->getSide() == Side::BUY)
    {
        buy();
    }
    else
    {
        sell();
    }
}

void MatchingEngine::sell()
{
    if (m_currentOrder->getType() == Type::MARKET)
    {
        m_ob->peekBestBid();
    }
    else
    {
    }
}

void MatchingEngine::buy() {}

// if (order->getSide() == Side::BUY)
//     {
//         auto bestAsk = m_ob->peekBestAsk();
//         if (bestAsk)
//         {
//             int diff = bestAsk->getQuantity() - order->getQuantity();
//             if (diff > 0)
//             {
//                 bestAsk->setQuantity(diff);
//             }
//             else if (diff < 0)
//             {
//                 order->setQuantity(-diff);
//             }

//             if (diff == 0)
//             {
//                 m_ob->fillOrder(std::move(order));
//             }
//         }
//     }
//     else
//     {
//         auto bestBid = m_ob->peekBestBid();
//         if (bestBid)
//         {
//         }
//     }
