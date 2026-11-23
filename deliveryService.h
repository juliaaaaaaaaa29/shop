#pragma once
#include <iostream>
#include <string>

class DeliveryService {
public:
    bool isAvailable(const std::string& type) {
        return (type == "courier" || type == "pickup" || type == "post");
    }

    double calculateCost(const std::string& type) {
        if (type == "courier") return 500.0;
        if (type == "post") return 200.0;
        return 0.0; 
    }

    void scheduleDelivery(int orderId) {
        std::cout << "[Доставка] Заказ " << orderId << " передан курьеру.\n";
    }
};