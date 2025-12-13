#include <memory>

#include "MatchingEngine.h"
#include "Order.h"
#include "OrderBook.h"
#include "OrderGenerator.h"

using std::cout, std::endl;

int main()
{
    std::shared_ptr<OrderBook> orderBook{std::make_shared<OrderBook>()};

    MatchingEngine matcher{orderBook};

    // Fill the order book with limit orders
    auto newOrders = OrderGenerator::genOrders(Type::LIMIT);

    for (const auto ord : newOrders)
    {
        orderBook->addOrder(ord);
    }
    //---------------------------------------

    // newOrders = OrderGenerator::genOrders(Type::MARKET, 200);
    // for (const auto ord : newOrders)
    // {
    //     matcher.match(ord);
    // }

    cout << endl;

    orderBook->showOrders();
    orderBook->removeOrder(1);
    orderBook->removeOrder(3);

    orderBook->showOrders();

    return 0;
}
