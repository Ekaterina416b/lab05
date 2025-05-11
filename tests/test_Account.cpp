#include "mocks/MockAccount.h"
#include "../../third-party/gtest/googletest/include/gtest/gtest.h"
TEST(AccountTest, Banking) {
    MockAccount test(0, 0);

    // Настройка ожиданий
    EXPECT_CALL(test, Lock()).Times(1);
    EXPECT_CALL(test, Unlock()).Times(1);
    EXPECT_CALL(test, ChangeBalance(100)).Times(1);
    EXPECT_CALL(test, GetBalance()).WillRepeatedly(::testing::Return(100));

    // Тестирование
    ASSERT_EQ(test.GetBalance(), 0);
    ASSERT_THROW(test.ChangeBalance(100), std::runtime_error);

    test.Lock();
    ASSERT_NO_THROW(test.ChangeBalance(100));
    ASSERT_EQ(test.GetBalance(), 100);
    ASSERT_THROW(test.Lock(), std::runtime_error);

    test.Unlock();
    ASSERT_THROW(test.ChangeBalance(100), std::runtime_error);
}
