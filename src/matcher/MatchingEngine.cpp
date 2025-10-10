// #include "MatchingEngine.h"

// #include <memory>
// #include <utility>

// #include "Order.h"

// /* Logic:
//     Order in -> Check if Market -> match immedietly with top result
//     Order in -> Check if Limit -> check to see if price of top is more/less -> add to queue if
//     other
//    orders come before

//                                                                             -> fill order if only
//    one at that price and matchs top oppposite

// */

// // Market orders, price is not checked, orders are filled automatically
// void MatchingEngine::match(std::unique_ptr<Order> order)
// {
//     m_currentOrder = std::move(order);

//     if (m_currentOrder->getSide() == Side::BUY)
//     {
//         if (m_ob->peekBestAsk()->get())
//         {
//             buy();
//         }
//         else
//         {
//             m_ob->addOrder(std::move(m_currentOrder));
//         }
//     }
//     else
//     {
//         if (m_ob->peekBestBid()->get())
//         {
//             sell();
//         }
//         else
//         {
//             m_ob->addOrder(std::move(m_currentOrder));
//         }
//     }
// }

// void MatchingEngine::sell()
// {
//     auto bestBid = m_ob->peekBestBid()->get();

//     long long bidID        = bestBid->getID();
//     double    bestPrice    = bestBid->getPrice();
//     int       bestQuantity = bestBid->getQuantity();

//     const long long orderID  = m_currentOrder->getID();
//     const double    price    = m_currentOrder->getPrice();
//     const int       quantity = m_currentOrder->getQuantity();

//     bool currentOrderFilled{false};

//     while (!currentOrderFilled)
//     {
//         if (quantity <= bestQuantity)
//         {
//             // Add the trade -> set the new quant for first item in list -> reset the order as it
//             is
//             // now filled
//             completedTrades.push_back(Trade(bidID, orderID, bestPrice, quantity));

//             bestBid->setQuantity(bestQuantity - quantity);
//             m_currentOrder.reset();
//             currentOrderFilled = true;

//             // Remove the top bid if that is also filled
//             if (quantity == bestQuantity)
//             {
//                 m_ob->removeBid(m_ob->peekBestBid());
//             }
//         }
//         else
//         {
//             completedTrades.push_back(Trade(bidID, orderID, bestPrice, bestQuantity));
//             m_ob->removeBid(m_ob->peekBestBid());

//             bestBid = m_ob->peekBestBid()->get();
//             if (!bestBid)
//             {
//                 m_ob->addOrder(std::move(m_currentOrder));
//             }
//         }
//     }
// }

// void MatchingEngine::buy() {}
