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
    static std::vector<Order> genOrders(Type marketType, int quant = 100)
    {
        std::vector<Order> orderList{};
        orderList.reserve(quant);

        for (int i = 0; i < quant / 2; i++)
        {
            orderList.emplace_back((i % 23) * 100, (i % 13) * 2, Side::SELL, marketType);
            orderList.emplace_back((i % 50) * 100, i % 13, Side::BUY, marketType);
        }

        return orderList;
    }
};

#endif /* D94AADB3_626F_4804_9DD7_55AE4C43962A */
