add_executable(MatchingEngine_tests
    MatchingEngineTests.cpp
)

target_link_libraries(MatchingEngine_tests
    PRIVATE
    matcher
    GTest::gtest
    GTest::gtest_main
)
target_compile_definitions(MatchingEngine_tests PRIVATE UNIT_TEST)

include(GoogleTest)
gtest_discover_tests(MatchingEngine_tests)
