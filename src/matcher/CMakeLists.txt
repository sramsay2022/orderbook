set(Sources
    MatchingEngine.cpp
)

add_library(matcher ${Sources})

target_include_directories(matcher 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(matcher
    PUBLIC
    order
    )

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
