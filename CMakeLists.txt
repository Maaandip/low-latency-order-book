cmake_minimum_required(VERSION 3.15)
project(OrderBook)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

add_executable(order_book
    src/main.cpp
    src/OrderBook.cpp
    src/FIXParser.cpp
    src/MatchingEngine.cpp
    src/TCPServer.cpp
)

target_include_directories(order_book PRIVATE src)