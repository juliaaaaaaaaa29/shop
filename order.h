#pragma once
#include <string>
#include <map>      
#include <iostream>

enum class OrderStatus { Pending, Paid, Shipped, Delivered, Cancelled };

class Order {
    int id;
    std::string customer;
    std::map<int, int> items; 
    OrderStatus status;
    std::string deliveryType;
    double totalPrice;

public:
    Order(int id, std::string cust, std::map<int, int> items, std::string delivery, double total)
        : id(id), customer(cust), items(items), status(OrderStatus::Pending), deliveryType(delivery), totalPrice(total) {
    }

    int getId() const { return id; }
    OrderStatus getStatus() const { return status; }
    void setStatus(OrderStatus s) { status = s; }
    double getTotalPrice() const { return totalPrice; }

    const std::map<int, int>& getItems() const { return items; }

    void print() const {
        std::string s = (status == OrderStatus::Pending) ? "Pending" :
            (status == OrderStatus::Paid) ? "Paid" :
            (status == OrderStatus::Shipped) ? "Shipped" : "Cancelled";
        std::cout << "Заказ ID: " << id << " | Клиент: " << customer << " | Статус: " << s << " | Сумма: " << totalPrice << "\n";
        std::cout << "  Товары: ";
        for (const auto& pair : items) {
            std::cout << "[ID " << pair.first << " x" << pair.second << "] ";
        }
        std::cout << "\n";
    }
};