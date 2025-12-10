#ifndef FF82AEC3_EE59_4C0D_A698_822F76DEC3D9
#define FF82AEC3_EE59_4C0D_A698_822F76DEC3D9

#include <chrono>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>

// enum class avoids implicit conversion to int (reduce bugs)
// : uint8_t sets the type to 8bits instead of 4bytes which default

enum class Side : uint8_t
{
    BUY,
    SELL
};

enum class Type : uint8_t
{
    MARKET,
    LIMIT
};

const std::map<Side, std::string> sideMap = {{Side::BUY, "BUY"}, {Side::SELL, "SELL"}};
const std::map<Type, std::string> typeMap = {{Type::MARKET, "MARKET"}, {Type::LIMIT, "LIMIT"}};

using std::cout, std::endl;
using Time = std::chrono::system_clock;

class Order
{
 public:
    Order() = delete;
    Order(int quantity, int price, Side side, Type type)
        : m_quantity{quantity}
        , m_price{price}
        , m_side{side}
        , m_type(type)
    {
        static long long genID{0};
        m_ID = ++genID;
    };
    ~Order() = default;

    void setQuantity(int x) { m_quantity = x; };
    int  getQuantity() const { return m_quantity; }

    long long        getID() const { return m_ID; }
    int              getPrice() const { return m_price; }
    Time::time_point getTime() const { return m_timestamp; }
    Side             getSide() const { return m_side; }
    Type             getType() const { return m_type; }

    void printDetails() const
    {
        cout << "m_ID: " << m_ID << ", Quantity: " << m_quantity << " @ " << m_price
             << ", Type: " << sideMap.at(m_side) << endl;
    }

 private:
    long long  m_ID{};
    int        m_quantity{};
    const int  m_price{};
    const Side m_side{};
    const Type m_type{};

    const Time::time_point m_timestamp{Time::now()};
};

struct Trade
{
    Trade(long long buyId, long long sellId, double p, int q)
        : m_buyOrderId(buyId)
        , m_sellOrderId(sellId)
        , m_price(p)
        , m_quantity(q)
    {
        static long long genTradeID{0};
        m_tradeId = ++genTradeID;
    }

    long long m_tradeId{};

    const long long m_buyOrderId{};
    const long long m_sellOrderId{};
    const double    m_price{};
    const int       m_quantity{};

    Time::time_point timestamp{Time::now()};
};

#endif /* FF82AEC3_EE59_4C0D_A698_822F76DEC3D9 */
