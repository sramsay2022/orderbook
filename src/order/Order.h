#ifndef FF82AEC3_EE59_4C0D_A698_822F76DEC3D9
#define FF82AEC3_EE59_4C0D_A698_822F76DEC3D9

#include <chrono>
#include <cstdint>
#include <format>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string_view>

/*
    Notes:
    - enum class avoids implicit conversion to int (reduce bugs)
    - uint8_t sets the type to 8bits instead of 4bytes which default
    - Use string_view as it is read only and no need to alocate

    @TODO Use random number generator rather than sequential for ID
*/

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

const std::map<Side, std::string_view>      sideMap = {{Side::BUY, "BUY"}, {Side::SELL, "SELL"}};
const std::map<OrderType, std::string_view> typeMap = {{OrderType::MARKET, "MARKET"},
                                                       {OrderType::LIMIT, "LIMIT"}};

using std::cout, std::endl;

using ID       = uint64_t;
using Time     = std::chrono::system_clock;
using Price    = uint32_t;
using Quantity = uint32_t;

struct OrderID
{
    static ID genId()
    {
        static std::atomic<ID> id{1};
        return id.fetch_add(1);
    }
};
struct TradeID
{
    static ID genId()
    {
        static std::atomic<ID> id{1};
        return id.fetch_add(1);
    }
};

class Order
{
 public:
    Order() = delete;
    Order(Quantity quantity, Price price, Side side, OrderType type)
        : m_ID(OrderID::genId())
        , m_quantity{quantity}
        , m_price{price}
        , m_side{side}
        , m_type(type) {};

    ~Order() = default;

    ID               getID() const { return m_ID; }
    Price            getPrice() const { return m_price; }
    Time::time_point getTime() const { return m_timestamp; }
    Side             getSide() const { return m_side; }
    OrderType        getType() const { return m_type; }

    Quantity getQuantity() const { return m_quantity; }
    void     setQuantity(Quantity x) { m_quantity = x; }

    void reduceQuantity(Quantity takeQty)
    {
        if (takeQty > m_quantity)
            throw std::logic_error(
                std::format("Error: cant have takeQty bigger than quantity:{}", getQuantity()));
        m_quantity -= takeQty;
    }

    bool isFilled() const { return m_quantity == 0; }
    bool isLimit() const { return OrderType::LIMIT == m_type; }
    bool isMarket() const { return OrderType::MARKET == m_type; }

    // TODO: may remove but keeping for readability for now
    bool isBuy() const { return Side::BUY == m_side; }
    bool isSell() const { return Side::SELL == m_side; }

    void printDetails() const
    {
        cout << "m_ID: " << m_ID << ", Quantity: " << m_quantity << " @ " << m_price
             << ", Side: " << sideMap.at(m_side) << endl;
    }

 private:
    ID              m_ID{};
    Quantity        m_quantity{};
    const Price     m_price{};  // Price in cents
    const Side      m_side{};
    const OrderType m_type{};

    const Time::time_point m_timestamp{Time::now()};
};

struct Trade
{
    Trade(ID buyId, ID sellId, Price p, Quantity q)
        : m_tradeId(TradeID::genId())
        , m_buyOrderId(buyId)
        , m_sellOrderId(sellId)
        , m_price(p)
        , m_quantity(q)
    {
    }

    void printDetails() const
    {
        cout << "m_tradeId: " << m_tradeId << ", Quantity: " << m_quantity << " @ " << m_price
             << " SellOrderId: " << m_sellOrderId << " BuyOrderId: " << m_buyOrderId << endl;
    }

    ID m_tradeId{};

    const ID       m_buyOrderId{};
    const ID       m_sellOrderId{};
    const Price    m_price{};
    const Quantity m_quantity{};

    const Time::time_point timestamp{Time::now()};
};

#endif /* FF82AEC3_EE59_4C0D_A698_822F76DEC3D9 */
