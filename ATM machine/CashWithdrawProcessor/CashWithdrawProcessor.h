#pragma once
#include <memory>
#include <vector>
#include "../Atm.h"
using namespace std;

class CashWithdrawProcessor {
protected:
    shared_ptr<CashWithdrawProcessor> nextProcessor;

    // Generic deduction logic
    void processDeduction(int atmNoteCount, int denomination, int deductionIndex,
                          int withdrawMoney, shared_ptr<Atm> atm, vector<int>& deductions) {
        int required = withdrawMoney / denomination;
        int balance = withdrawMoney % denomination;

        if (atmNoteCount < required) {
            deductions[deductionIndex] = atmNoteCount;
            balance += (required - atmNoteCount) * denomination;
        } else {
            deductions[deductionIndex] = required;
        }

        if (balance > 0) {
            if (nextProcessor) {
                nextProcessor->deductMoney(atm, balance, deductions);
                if (deductions.empty()) return; // propagate failure
            } else {
                deductions.clear(); // not enough notes
            }
        }
    }

public:
    CashWithdrawProcessor() : nextProcessor(nullptr) {}
    virtual ~CashWithdrawProcessor() = default;

    void setNextProcessor(shared_ptr<CashWithdrawProcessor> newProcessor) {
        nextProcessor = newProcessor;
    }

    virtual void deductMoney(shared_ptr<Atm> atm, int withdrawMoney, vector<int>& deductions) = 0;
};

// 2000 Rs processor
class twoThousandsProcessor : public CashWithdrawProcessor {
public:
    void deductMoney(shared_ptr<Atm> atm, int withdrawMoney, vector<int>& deductions) override {
        processDeduction(atm->getTwoThousandCount(), 2000, 0, withdrawMoney, atm, deductions);
    }
};

// 500 Rs processor
class fiveHundredProcessor : public CashWithdrawProcessor {
public:
    void deductMoney(shared_ptr<Atm> atm, int withdrawMoney, vector<int>& deductions) override {
        processDeduction(atm->getFiveHundredCount(), 500, 1, withdrawMoney, atm, deductions);
    }
};

// 100 Rs processor
class oneHundredProcessor : public CashWithdrawProcessor {
public:
    void deductMoney(shared_ptr<Atm> atm, int withdrawMoney, vector<int>& deductions) override {
        processDeduction(atm->getOneHundredCount(), 100, 2, withdrawMoney, atm, deductions);
    }
};
