#ifndef B0E62D57_CE6D_435D_92B9_7DA64B93C6A9
#define B0E62D57_CE6D_435D_92B9_7DA64B93C6A9

#include <chrono>
#include <map>
#include <string_view>

using ID       = uint64_t;
using Price    = uint32_t;
using Quantity = uint32_t;
using Time     = std::chrono::system_clock;

// Used for Market Orders
struct Constants
{
    static const Price InvalidPrice = std::numeric_limits<Price>::quiet_NaN();
};

// Disallow implicit conversions
enum class Side : uint8_t
{
    BUY,
    SELL
};

enum class OrderType : uint8_t
{
    MARKET,
    LIMIT
};

// For readability with print statements, not actually needed, may remove
const std::map<Side, std::string_view>      sideMap = {{Side::BUY, "BUY"}, {Side::SELL, "SELL"}};
const std::map<OrderType, std::string_view> typeMap = {{OrderType::MARKET, "MARKET"},
                                                       {OrderType::LIMIT, "LIMIT"}};

#endif /* B0E62D57_CE6D_435D_92B9_7DA64B93C6A9 */
