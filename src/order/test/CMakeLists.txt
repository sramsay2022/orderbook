add_executable(orderbook_tests
    OrderTests.cpp
)

target_link_libraries(orderbook_tests
    PRIVATE
    order
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(orderbook_tests)
