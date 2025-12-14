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
    auto newOrders = OrderGenerator::generateSampleOrders();

    for (const auto ord : newOrders)
    {
        orderBook->addOrder(ord);
    }
    //---------------------------------------
    matcher.listTrades();

    Order o{10000, 90, Side::SELL, OrderType::MARKET};
    matcher.match(o);

    Order o2{10, 90, Side::BUY, OrderType::MARKET};
    matcher.match(o2);

    matcher.listTrades();
    cout << endl;

    return 0;
}
