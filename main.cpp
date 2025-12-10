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

    OrderGenerator ordGen{Type::MARKET};

    auto newOrders = std::move(ordGen).getOrders();

    cout << "Order book" << endl;

    for (const auto ord : newOrders)
    {
        orderBook->addOrder(std::move(ord));
    }

    cout << endl;

    orderBook->showOrders();

    return 0;
}
