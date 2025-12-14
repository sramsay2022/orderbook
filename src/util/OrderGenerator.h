#ifndef D94AADB3_626F_4804_9DD7_55AE4C43962A
#define D94AADB3_626F_4804_9DD7_55AE4C43962A

#include <vector>

#include "Order.h"

/*
    Notes:
    - Made OrderGenerator stateless which means I dont have to create a throwaway object
    - Added reserve() as the size of the vector is known before hand and can be used to eliminate
      reallocations if the size is known beforehand.

    By making the struct stateless and the function static I can call it from anywhere and as vector
    supports moves and NRVO it reduces overhead by:
    - Moves object to new owner (cheap)
    - Doesnt have to clean up vector after return as its been moved elsewhere (cheap)
*/

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

        int bestBid = 99;
        int bestAsk = 100;

        // --- Generate 10 BUY limit orders ---
        for (int i = 0; i < 10; ++i)
        {
            int price = bestBid - i;     // 99, 98, 97, ...
            int qty   = 100 + (i * 10);  // 100, 110, 120, ...

            orders.emplace_back(qty, price, Side::BUY, OrderType::LIMIT);
        }

        // --- Generate 10 SELL limit orders ---
        for (int i = 0; i < 10; ++i)
        {
            int price = bestAsk + i;  // 100, 101, 102, ...
            int qty   = 100 + (i * 10);

            orders.emplace_back(qty, price, Side::SELL, OrderType::LIMIT);
        }

        return orders;
    }
};

#endif /* D94AADB3_626F_4804_9DD7_55AE4C43962A */
