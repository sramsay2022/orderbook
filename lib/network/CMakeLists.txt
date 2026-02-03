set(Sources
    Server.cpp
)

add_library(Server ${Sources})

target_include_directories(matcher 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

    target_link_libraries(Server PUBLIC util)
