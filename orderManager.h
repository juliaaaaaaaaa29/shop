#pragma once
#include <map>
#include <memory>
#include "Order.h"

class OrderManager {
    std::map<int, std::shared_ptr<Order>> orders;
    int nextOrderId = 1;
public:
    int createOrder(std::string customer, std::map<int, int> items, std::string delivery, double total) {
        int id = nextOrderId++;
        orders[id] = std::make_shared<Order>(id, customer, items, delivery, total);
        return id;
    }

    void cancelOrder(int orderId) {
        if (orders.count(orderId) && orders[orderId]->getStatus() != OrderStatus::Shipped) {
            orders[orderId]->setStatus(OrderStatus::Cancelled);
            std::cout << "[Заказы] Заказ " << orderId << " отменен.\n";
        }
    }

    void confirmPayment(int orderId) {
        if (orders.count(orderId)) {
            orders[orderId]->setStatus(OrderStatus::Paid);
            std::cout << "[Заказы] Заказ " << orderId << " оплачен.\n";
        }
    }

    void shipOrder(int orderId) {
        if (orders.count(orderId)) {
            orders[orderId]->setStatus(OrderStatus::Shipped);
            std::cout << "[Заказы] Заказ " << orderId << " отправлен.\n";
        }
    }

    std::shared_ptr<Order> getOrder(int orderId) {
        if (orders.count(orderId)) return orders[orderId];
        return nullptr;
    }

    void listOrders() const {
        for (const auto& pair : orders) pair.second->print();
    }

    void getStatistics() const {
        double turnover = 0;
        for (const auto& pair : orders) {
            if (pair.second->getStatus() == OrderStatus::Paid) turnover += pair.second->getTotalPrice();
        }
        std::cout << "[Статистика] Заказов: " << orders.size() << " | Оборот: " << turnover << " руб.\n";
    }
};