#pragma once
#include "warehouse.h"
#include "order.h"
#include "orderManager.h"
#include "deliveryService.h"
#include "paymentSystem.h"
#include <vector>
#include <map>
#include <iostream>

class ShopMediator {
    Warehouse& warehouse;
    OrderManager& orderManager;
    PaymentSystem& paymentSystem;
    DeliveryService& deliveryService;
public:
    ShopMediator(Warehouse& w, OrderManager& om, PaymentSystem& ps, DeliveryService& ds)
        : warehouse(w), orderManager(om), paymentSystem(ps), deliveryService(ds) {
    }

    int createOrder(const std::string& customer, const std::map<int, int>& itemIds, const std::string& deliveryType) {
        if (!deliveryService.isAvailable(deliveryType)) {
            std::cout << "[Медиатор] Ошибка: Доставка недоступна.\n";
            return -1;
        }

        double total = 0;

        for (const auto& pair : itemIds) {
            int id = pair.first;
            int qty = pair.second;
            Product* p = warehouse.findById(id);
            if (!p) {
                std::cout << "[Медиатор] Ошибка: Товар " << id << " не найден.\n";
                return -1;
            }
            if (p->getQuantity().getValue() < qty) {
                std::cout << "[Медиатор] Ошибка: Товара " << id << " недостаточно (нужно " << qty << ").\n";
                return -1;
            }
        }

        for (const auto& pair : itemIds) {
            int id = pair.first;
            int qty = pair.second;
            total += warehouse.getProductPrice(id) * qty;
            warehouse.changeQuantity(id, -qty); 
        }

        total += deliveryService.calculateCost(deliveryType);

        int orderId = orderManager.createOrder(customer, itemIds, deliveryType, total);
        std::cout << "[Медиатор] Заказ " << orderId << " создан. Сумма: " << total << " руб.\n";
        return orderId;
    }

    void cancelOrder(int orderId) {
        auto order = orderManager.getOrder(orderId);
        if (order && order->getStatus() != OrderStatus::Shipped) {
            for (const auto& pair : order->getItems()) {
                warehouse.changeQuantity(pair.first, pair.second);
            }
            std::cout << "[Медиатор] Товары из заказа " << orderId << " возвращены на склад.\n";
        }
        orderManager.cancelOrder(orderId);
    }

    void confirmPayment(int orderId) { orderManager.confirmPayment(orderId); }
    void shipOrder(int orderId) { orderManager.shipOrder(orderId); }
    void getStatistics() { orderManager.getStatistics(); }
    void listOrders() { orderManager.listOrders(); }
};