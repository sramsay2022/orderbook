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
    Order order{100, 50, Side::BUY, OrderType::LIMIT};

    std::unique_ptr<OrderBook> m_obUnderTest;
};

TEST_F(OrderBookTests, addOrderTests)
{
    EXPECT_EQ(m_obUnderTest->isAskEmpty(), true);
    EXPECT_EQ(m_obUnderTest->isBidEmpty(), true);

    m_obUnderTest->addOrder(order);

    EXPECT_EQ(m_obUnderTest->isBidEmpty(), false);
    EXPECT_EQ(m_obUnderTest->isAskEmpty(), true);
}

TEST_F(OrderBookTests, SetQuantityTest)
{
    order.setQuantity(150);
    EXPECT_EQ(order.getQuantity(), 150);
}

TEST_F(OrderBookTests, ReduceQuantityTest)
{
    order.reduceQuantity(50);
    EXPECT_EQ(order.getQuantity(), 50);
}

TEST_F(OrderBookTests, ReduceQuantityExceedsTest)
{
    EXPECT_THROW(order.reduceQuantity(150), std::logic_error);
}

TEST_F(OrderBookTests, IsFilledTest)
{
    EXPECT_FALSE(order.isFilled());
    order.reduceQuantity(100);
    EXPECT_TRUE(order.isFilled());
}

TEST_F(OrderBookTests, IsLimitTest)
{
    EXPECT_TRUE(order.isLimit());
    EXPECT_FALSE(order.isMarket());
}

TEST_F(OrderBookTests, IsBuyTest)
{
    EXPECT_TRUE(order.isBuy());
    EXPECT_FALSE(order.isSell());
}
