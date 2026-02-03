#ifndef D94AADB3_626F_4804_9DD7_55AE4C43962A
#define D94AADB3_626F_4804_9DD7_55AE4C43962A

#include <vector>

#include "Order.h"
#include "Types.h"

struct OrderGenerator
{
    static std::vector<Order> genOrders(OrderType marketType, int quant = 10000)
    {
        std::vector<Order> orders{};
        orders.reserve(quant);

        for (int i = 0; i < quant; i++)
        {
            orders.emplace_back((i % 50) * 100, i % 13, Side::BUY, marketType);
            orders.emplace_back((i % 23) * 100, (i % 13) * 50000, Side::SELL, marketType);
        }

        return orders;
    }

    static std::vector<Order> generateSampleOrders()
    {
        std::vector<Order> orders;
        orders.reserve(20);

        Price bestBid = 99;
        Price bestAsk = 100;

        // --- Generate 10 BUY limit orders ---
        for (int i = 0; i < 10; ++i)
        {
            Price    price = bestBid - i;     // 99, 98, 97, ...
            Quantity qty   = 100 + (i * 10);  // 100, 110, 120, ...

            orders.emplace_back(qty, price, Side::BUY, OrderType::LIMIT);
        }

        // --- Generate 10 SELL limit orders ---
        for (int i = 0; i < 10; ++i)
        {
            Price    price = bestAsk + i;  // 100, 101, 102, ...
            Quantity qty   = 100 + (i * 10);

            orders.emplace_back(qty, price, Side::SELL, OrderType::LIMIT);
        }

        return orders;
    }
};

#endif /* D94AADB3_626F_4804_9DD7_55AE4C43962A */
