set(Sources
    OrderBook.cpp
)

add_library(order ${Sources})

target_include_directories(order 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(order
    PUBLIC
    util)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
