#include "Transaction.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "Account.h"

namespace {
// RAII
struct Guard {
  Guard(Account& account) : account_(&account) { account_->Lock(); }

  ~Guard() { account_->Unlock(); }

 private:
  Account* account_;
};
}  // namespace

Transaction::Transaction() : fee_(1) {}

Transaction::~Transaction() {}

bool Transaction::Make(Account& from, Account& to, int sum) {
  if (from.id() == to.id()) throw std::logic_error("invalid action");

  if (sum < 0) throw std::invalid_argument("sum can't be negative");

  if (sum < 100) throw std::logic_error("too small");

  if (fee_ * 2 > sum) return false;

  Guard guard_from(from);
  Guard guard_to(to);

  // 1. Попытка списания средств с отправителя (с учетом комиссии)
  if (!Debit(from, sum + fee_)) {
    return false; // Недостаточно средств на счете from, отмена транзакции
  }

  // 2. Если списание успешно, зачисление на счет получателя
  Credit(to, sum);

  // 3. Сохранение в БД (после успешного списания и зачисления)
  SaveToDataBase(from, to, sum);

  return true; // Транзакция успешна
}

void Transaction::Credit(Account& accout, int sum) {
  assert(sum > 0);
  accout.ChangeBalance(sum);
}

bool Transaction::Debit(Account& accout, int sum) {
  assert(sum > 0);
  if (accout.GetBalance() >= sum) { // Исправлено: >=
    accout.ChangeBalance(-sum);
    return true;
  }
  return false;
}

void Transaction::SaveToDataBase(Account& from, Account& to, int sum) {
  std::cout << from.id() << " send to " << to.id() << " $" << sum << std::endl;
  std::cout << "Balance " << from.id() << " is " << from.GetBalance()
            << std::endl;
  std::cout << "Balance " << to.id() << " is " << to.GetBalance() << std::endl;
}
