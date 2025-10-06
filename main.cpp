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

    OrderGenerator ordGen{};

    auto newOrders{ordGen.getOrders()};

    cout << "Order book" << endl;

    for (const auto o : newOrders)
    {
        auto ord = std::make_unique<Order>(*o);

        matcher.match(std::move(ord));
    }

    cout << endl;

    orderBook->showOrders();

    return 0;
}
