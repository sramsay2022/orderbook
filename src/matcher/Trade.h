#ifndef A2E32D96_675E_4AEB_A768_4C765D0757D8
#define A2E32D96_675E_4AEB_A768_4C765D0757D8

#include <map>

#include "Order.h"

// This class stores all the trades made.

struct Trade
{
    std::map<Order, Order> trades{};
};

#endif /* A2E32D96_675E_4AEB_A768_4C765D0757D8 */
