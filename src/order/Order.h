#ifndef FF82AEC3_EE59_4C0D_A698_822F76DEC3D9
#define FF82AEC3_EE59_4C0D_A698_822F76DEC3D9

#include <chrono>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>

enum class ORDER : uint8_t
{
    BUY,
    SELL
};
const std::map<ORDER, std::string> OrderMap = {{ORDER::BUY, "BUY"}, {ORDER::SELL, "SELL"}};

using std::cout, std::endl;
using Time = std::chrono::system_clock;

class Order
{
 public:
    Order() = delete;
    Order(int quantity, double price, ORDER orderType)
        : m_quantity{quantity}
        , m_price{price}
        , m_orderType{orderType}
    {
        static long long genID{0};
        m_ID = ++genID;
    };
    ~Order() = default;

    void partialFill();

    void setQuantity(int);
    int  getQuantity() const { return m_quantity; }

    long long        getID() const { return m_ID; }
    double           getPrice() const { return m_price; }
    Time::time_point getTime() const { return m_timestamp; }
    ORDER            getOrderType() const { return m_orderType; }

    void printDetails() const
    {
        cout << "m_ID: " << m_ID << ", Price: " << m_price << ", Time: " << m_timestamp
             << ", Type: " << OrderMap.at(m_orderType) << endl;
    }

 private:
    long long    m_ID{};
    int          m_quantity{};
    const double m_price{};
    const ORDER  m_orderType{};

    const Time::time_point m_timestamp{Time::now()};
};

#endif /* FF82AEC3_EE59_4C0D_A698_822F76DEC3D9 */
