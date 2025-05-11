#pragma once
#include "../banking/Transaction.h"
#include <gmock/gmock.h>

class MockTransaction : public Transaction {
public:
    MOCK_METHOD(int, fee, (), (const));
    MOCK_METHOD(void, set_fee, (int fee));
    MOCK_METHOD(bool, Make, (Account& from, Account& to, int amount));
};
