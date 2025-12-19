#include <gtest/gtest.h>

#include "Order.h"

class OrderTests : public ::testing::Test
{
 protected:
    Order* order;

    void SetUp() override { order = new Order(100, 50, Side::BUY, OrderType::LIMIT); }

    void TearDown() override { delete order; }
};

TEST_F(OrderTests, ConstructorTest)
{
    EXPECT_EQ(order->getQuantity(), 100);
    EXPECT_EQ(order->getPrice(), 50);
    EXPECT_EQ(order->getSide(), Side::BUY);
    EXPECT_EQ(order->getType(), OrderType::LIMIT);
}

TEST_F(OrderTests, SetQuantityTest)
{
    order->setQuantity(150);
    EXPECT_EQ(order->getQuantity(), 150);
}

TEST_F(OrderTests, ReduceQuantityTest)
{
    order->reduceQuantity(50);
    EXPECT_EQ(order->getQuantity(), 50);
}

TEST_F(OrderTests, ReduceQuantityExceedsTest)
{
    EXPECT_THROW(order->reduceQuantity(150), std::logic_error);
}

TEST_F(OrderTests, IsFilledTest)
{
    EXPECT_FALSE(order->isFilled());
    order->reduceQuantity(100);
    EXPECT_TRUE(order->isFilled());
}

TEST_F(OrderTests, IsLimitTest)
{
    EXPECT_TRUE(order->isLimit());
    EXPECT_FALSE(order->isMarket());
}

TEST_F(OrderTests, IsBuyTest)
{
    EXPECT_TRUE(order->isBuy());
    EXPECT_FALSE(order->isSell());
}
