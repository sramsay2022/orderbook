#ifndef D94AADB3_626F_4804_9DD7_55AE4C43962A
#define D94AADB3_626F_4804_9DD7_55AE4C43962A

#include <vector>

#include "Order.h"

struct OrderGenerator
{
    OrderGenerator(Type marketType = Type::MARKET, int quant = 100)
    {
        for (int i = 0; i < quant; i++)
        {
            orderList.emplace_back((i % 50) * 100, i % 19, static_cast<Side>(i % 2), marketType);
        }
    }

    std::vector<Order> getOrders() && { return std::move(orderList); }

    std::vector<Order> orderList{};
};

#endif /* D94AADB3_626F_4804_9DD7_55AE4C43962A */
