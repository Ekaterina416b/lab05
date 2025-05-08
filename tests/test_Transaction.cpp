#include "mocks/MockAccount.h"
#include "mocks/MockTransaction.h"
#include <gtest/gtest.h>

TEST(TransactionTest, Banking) {
    MockAccount Alice(0, 5000), Bob(1, 5000);
    MockTransaction test_tran;

    // Настройка ожиданий
    EXPECT_CALL(test_tran, fee())
        .WillOnce(::testing::Return(1))
        .WillRepeatedly(::testing::Return(100));
    
    EXPECT_CALL(test_tran, set_fee(100)).Times(1);
    EXPECT_CALL(Alice, Lock()).Times(1);
    EXPECT_CALL(Alice, Unlock()).Times(1);

    // Тестирование
    ASSERT_EQ(test_tran.fee(), 1);
    test_tran.set_fee(100);
    ASSERT_EQ(test_tran.fee(), 100);

    ASSERT_THROW(test_tran.Make(Alice, Alice, 1000), std::logic_error);
    ASSERT_THROW(test_tran.Make(Alice, Bob, -50), std::invalid_argument);
    
    Alice.Lock();
    ASSERT_THROW(test_tran.Make(Alice, Bob, 1000), std::runtime_error);
    Alice.Unlock();
}
