cmake_minimum_required(VERSION 3.20)
project(banking LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная библиотека
add_library(banking
    banking/Account.cpp
    banking/Account.h
    banking/Transaction.cpp
    banking/Transaction.h
)
target_include_directories(banking PUBLIC 
    banking
)

# Тесты
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()
    
    # Подключение GoogleTest
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/third-party/gtest/CMakeLists.txt)
        add_subdirectory(third-party/gtest EXCLUDE_FROM_ALL)
    else()
        message(FATAL_ERROR "GoogleTest not found. Run: git submodule update --init")
    endif()

    
    add_library(banking_mocks INTERFACE)
    target_include_directories(banking_mocks INTERFACE 
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/mocks
    )
    target_link_libraries(banking_mocks INTERFACE 
        GTest::gtest
        GTest::gmock
    )

    # Тестовый исполняемый файл
    add_executable(banking_tests
        tests/test_Account.cpp
        tests/test_Transaction.cpp
    )

    target_link_libraries(banking_tests PRIVATE
    banking
    banking_mocks
    gtest
    gmock
    gtest_main
    )
endif()
