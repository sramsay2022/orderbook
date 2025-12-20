#include <gtest/gtest.h>

#include <memory>

#include "Order.h"
#include "OrderBook.h"

/*  void addOrder(const Order& order);
    void removeOrder(const long long id);

    auto& getBook(const Side side) { return (side == Side::BUY) ? m_bid : m_ask; }
    int peekBestBid() const { return std::prev(m_bid.end())->first; }
    int peekBestAsk() const { return m_ask.begin()->first; }
    bool isBidEmpty() const { return m_bid.empty(); }
    bool isAskEmpty() const { return m_ask.empty(); }
    auto getBestBid() { return std::prev(m_bid.end()); }
    auto getBestAsk() { return m_ask.begin(); }
*/

class OrderBookTests : public ::testing::Test
{
    void SetUp() override { m_obUnderTest = std::make_unique<OrderBook>(); }

 protected:
    Order buyOrder{100, 50, Side::BUY, OrderType::LIMIT};
    Order sellOrder{100, 60, Side::SELL, OrderType::LIMIT};

    std::unique_ptr<OrderBook> m_obUnderTest;
};

TEST_F(OrderBookTests, addOrderTest)
{
    EXPECT_TRUE(m_obUnderTest->isAskEmpty());
    EXPECT_TRUE(m_obUnderTest->isBidEmpty());

    m_obUnderTest->addOrder(buyOrder);
    EXPECT_FALSE(m_obUnderTest->isBidEmpty());
    EXPECT_TRUE(m_obUnderTest->isAskEmpty());

    m_obUnderTest->addOrder(sellOrder);
    EXPECT_FALSE(m_obUnderTest->isBidEmpty());
    EXPECT_FALSE(m_obUnderTest->isAskEmpty());
}

TEST_F(OrderBookTests, removeOrderTest) { m_obUnderTest->addOrder(buyOrder); }

TEST_F(OrderBookTests, getBookReturnsBidForBuyAndAskForSell)
{
    auto& bid = m_obUnderTest->getBook(Side::BUY);
    auto& ask = m_obUnderTest->getBook(Side::SELL);

    EXPECT_NE(&bid, &ask);
}

// 2 Order tests
TEST_F(OrderBookTests, ReduceQuantityTest)
{
    std::unique_ptr<Order> order =
        std::make_unique<Order>(Order{100, 50, Side::BUY, OrderType::LIMIT});
    order->reduceQuantity(50);
    EXPECT_EQ(order->getQuantity(), 50);
}

TEST_F(OrderBookTests, ReduceQuantityExceedsTest)
{
    std::unique_ptr<Order> order =
        std::make_unique<Order>(Order{100, 50, Side::BUY, OrderType::LIMIT});

    EXPECT_THROW(order->reduceQuantity(150), std::logic_error);
}
