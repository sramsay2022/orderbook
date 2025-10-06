#ifndef A2E32D96_675E_4AEB_A768_4C765D0757D8
#define A2E32D96_675E_4AEB_A768_4C765D0757D8

#include <chrono>
// Stores data from completed trades
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

    std::chrono::system_clock::time_point timestamp{std::chrono::system_clock::now()};
};

#endif /* A2E32D96_675E_4AEB_A768_4C765D0757D8 */
