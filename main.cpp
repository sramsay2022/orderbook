#include <memory>

#include "MatchingEngine.h"
#include "Order.h"
#include "OrderBook.h"
#include "OrderGenerator.h"
#include "Server.h"
#include "Timer.h"
#include "Types.h"

using std::cout, std::endl;

int main()
{
    Server test = Server("127.0.0.1", "8081");
    test.startListen();

    std::shared_ptr<OrderBook> orderBook{std::make_shared<OrderBook>()};

    MatchingEngine matcher{orderBook};

    // Fill the order book with limit orders
    auto newOrders = OrderGenerator::generateSampleOrders();

    for (auto& ord : newOrders)
    {
        orderBook->addOrder(ord);
    }
    //---------------------------------------

    Timer t;
    Order o{100, 90, Side::SELL, OrderType::MARKET};
    matcher.match(o);
    cout << "Time elapsed: " << t.elapsed_ssms() << endl;
    t.reset();
    Order o2{10000, 104, Side::BUY, OrderType::LIMIT};
    matcher.match(o2);
    cout << "Time elapsed: " << t.elapsed_ssms() << endl;
    matcher.listTrades();
    cout << endl;

    return 0;
}
