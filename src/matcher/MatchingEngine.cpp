#include "MatchingEngine.h"

#include <memory>

#include "OrderBook.h"
// Market orders, price is not checked, orders are filled automatically
void MatchingEngine::match(std::unique_ptr<Order> order)
{
    if (order->getOrderType() == ORDER::BUY)
    {
        auto bestAsk = m_ob->peekBestAsk();
        if (bestAsk)
        {
            int diff = bestAsk->getQuantity() - order->getQuantity();
            if (diff > 0)
            {
                bestAsk->setQuantity(diff);
            }
            else if (diff < 0)
            {
                order->setQuantity(-diff);
            }

            if (diff == 0)
            {
                m_ob->fillOrder(std::move(order));
            }
        }
    }
    else
    {
        auto bestBid = m_ob->peekBestBid();
        if (bestBid)
        {
        }
    }

    m_ob->addOrder(std::move(order));
}
