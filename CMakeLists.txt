cmake_minimum_required(VERSION 3.20)
project(banking LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная библиотека
add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)
target_include_directories(banking PUBLIC banking)

# Тесты
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()
    
    # Подключение GoogleTest (исправленная строка)
    add_subdirectory(third-party/gtest EXCLUDE_FROM_ALL)  # Используем существующий путь
    
    # Моки как INTERFACE-библиотека
    add_library(banking_mocks INTERFACE)
    target_include_directories(banking_mocks INTERFACE tests/mocks)
    target_link_libraries(banking_mocks INTERFACE GTest::gtest)

    # Тесты
    add_executable(banking_tests
        tests/test_Account.cpp
        tests/test_Transaction.cpp
    )
   
