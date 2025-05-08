cmake_minimum_required(VERSION 3.20)
project(banking LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная библиотека
add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)
target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/banking)

# Тесты
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()
    
    # Подключаем GoogleTest
    add_subdirectory(third-party/gtest)
    
    # Моки
    add_library(banking_mocks
        tests/mocks/MockAccount.h
        tests/mocks/MockTransaction.h
    )
    target_link_libraries(banking_mocks GTest::GTest)
    target_include_directories(banking_mocks PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/mocks
    )

    # Тестовый исполняемый файл
    add_executable(banking_tests
        tests/test_Account.cpp
        tests/test_Transaction.cpp
    )
    target_link_libraries(banking_tests
        banking
        banking_mocks
        GTest::GTest
        GTest::Main
    )
    
    add_test(NAME banking_tests COMMAND banking_tests)
endif()
