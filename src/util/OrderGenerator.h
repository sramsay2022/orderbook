#ifndef D94AADB3_626F_4804_9DD7_55AE4C43962A
#define D94AADB3_626F_4804_9DD7_55AE4C43962A

#include <vector>

#include "Order.h"

struct OrderGenerator
{
    OrderGenerator(int quant = 100)
    {
        for (int i = 0; i < quant; i++)
        {
            Order* o{new Order(i % 2, static_cast<double>(i % 439), static_cast<Side>(i % 2),
                               static_cast<Type>(i % 2))};
            orderList.push_back(o);
        }
    }
    std::vector<Order*> getOrders() const { return orderList; }

    std::vector<Order*> orderList{};
};

#endif /* D94AADB3_626F_4804_9DD7_55AE4C43962A */
