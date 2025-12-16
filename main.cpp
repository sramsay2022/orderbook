#include <memory>

#include "MatchingEngine.h"
#include "Order.h"
#include "OrderBook.h"
#include "OrderGenerator.h"
#include "Timer.h"

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

    Timer t;
    Order o{10000, 90, Side::SELL, OrderType::MARKET};
    matcher.match(o);
    cout << "Time elapsed: " << t.elapsed_ns() << endl;
    t.reset();
    Order o2{10, 90, Side::BUY, OrderType::MARKET};
    matcher.match(o2);
    cout << "Time elapsed: " << t.elapsed_ns() << endl;
    matcher.listTrades();
    cout << endl;

    return 0;
}
