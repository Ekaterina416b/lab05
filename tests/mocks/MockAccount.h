#pragma once
#include "../banking/Account.h"
#include <gmock/gmock.h>

class MockAccount : public Account {
public:
    MockAccount(int id = 0, int balance = 0) : Account(id, balance) {}
    
    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int amount), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
    MOCK_METHOD(int, id, (), (const, override));
};
