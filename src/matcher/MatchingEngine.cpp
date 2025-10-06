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
    auto bestBid = m_ob->peekBestBid()->get();

    const long long orderID  = m_currentOrder->getID();
    const double    price    = m_currentOrder->getPrice();
    const int       quantity = m_currentOrder->getQuantity();

    bool currentOrderFilled{false};

    while (currentOrderFilled)
    {  // if (m_currentOrder->getType() == Type::MARKET)
       //   {

        const long long bidID        = bestBid->getID();
        const double    bestPrice    = bestBid->getPrice();
        const int       bestQuantity = bestBid->getQuantity();

        completedTrades.push_back(Trade(bidID, orderID, bestPrice, quantity));

        if (quantity <= bestQuantity)
        {
            bestBid->setQuantity(bestQuantity - quantity);
            if (bestQuantity - quantity == 0)
            {
                m_ob->removeBid(m_ob->peekBestBid());
            }
            m_currentOrder.reset();
            currentOrderFilled = true;
        }
        else
        {
            completedTrades.push_back(Trade(bidID, orderID, bestPrice, quantity));
            m_ob->removeBid(m_ob->peekBestBid());

            bestBid = m_ob->peekBestBid()->get();
        }
        //   }
        //  else
        {
        }
    }
}

void MatchingEngine::buy() {}
