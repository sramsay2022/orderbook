#include <gtest/gtest.h>

#include <memory>

#include "MatchingEngine.h"
#include "Order.h"
#include "OrderBook.h"

class MatchingEngineTests : public ::testing::Test
{
    void SetUp() override {}

 protected:
    Order buyOrder{100, 50, Side::BUY, OrderType::LIMIT};
    Order sellOrder{100, 60, Side::SELL, OrderType::LIMIT};

    std::unique_ptr<MatchingEngine> m_matcherUnderTest;
};
