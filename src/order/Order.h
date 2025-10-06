#ifndef FF82AEC3_EE59_4C0D_A698_822F76DEC3D9
#define FF82AEC3_EE59_4C0D_A698_822F76DEC3D9

#include <chrono>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>

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

const std::map<Side, std::string> OrderMap = {{Side::BUY, "BUY"}, {Side::SELL, "SELL"}};

using std::cout, std::endl;
using Time = std::chrono::system_clock;

class Order
{
 public:
    Order() = delete;
    Order(int quantity, double price, Side side, Type type)
        : m_quantity{quantity}
        , m_price{price}
        , m_side{side}
        , m_type(type)
    {
        static long long genID{0};
        m_ID = ++genID;
    };
    ~Order() = default;

    void setQuantity(int);
    int  getQuantity() const { return m_quantity; }

    long long        getID() const { return m_ID; }
    double           getPrice() const { return m_price; }
    Time::time_point getTime() const { return m_timestamp; }
    Side             getSide() const { return m_side; }
    Type             getType() const { return m_type; }

    void printDetails() const
    {
        cout << "m_ID: " << m_ID << ", Quantity: " << m_quantity << "@ " << m_price
             << ", Time: " << m_timestamp << ", Type: " << OrderMap.at(m_side) << endl;
    }

 private:
    long long    m_ID{};
    int          m_quantity{};
    const double m_price{};
    const Side   m_side{};
    const Type   m_type{};

    const Time::time_point m_timestamp{Time::now()};
};

#endif /* FF82AEC3_EE59_4C0D_A698_822F76DEC3D9 */
