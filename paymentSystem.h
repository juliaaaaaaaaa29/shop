#pragma once
#include <iostream>

class PaymentSystem {
public:
    bool processPayment(int orderId, double amount) {
        std::cout << "[Оплата] Списано " << amount << " руб. за заказ " << orderId << "\n";
        return true;
    }
};