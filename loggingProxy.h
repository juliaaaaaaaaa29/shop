#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "shopFacade.h"
#include "comands.h"
#include <map>

class LoggingProxy {
    ShopFacade& realFacade_;
public:
    LoggingProxy(ShopFacade& facade) : realFacade_(facade) {}

    void addProduct(std::unique_ptr<Product> product) {
        std::cout << "[LOG] Вызов addProduct\n";
        realFacade_.addProduct(std::move(product));
    }

    void changePrice(int id, int newPrice) {
        std::cout << "[LOG] Вызов changePrice для ID " << id << "\n";
        realFacade_.changePrice(id, newPrice);
    }

    void changeQuantity(int id, int delta) {
        std::cout << "[LOG] Вызов changeQuantity для ID " << id << "\n";
        realFacade_.changeQuantity(id, delta);
    }

    void createOrder(const std::string& c, const std::map<int, int>& i, const std::string& d) {
        std::cout << "[LOG] Вызов createOrder\n";
        realFacade_.createOrder(c, i, d);
    }

    void confirmPayment(int id) {
        std::cout << "[LOG] Вызов confirmPayment для заказа " << id << "\n";
        realFacade_.confirmPayment(id);
    }

    void shipOrder(int id) {
        std::cout << "[LOG] Вызов shipOrder для заказа " << id << "\n";
        realFacade_.shipOrder(id);
    }

    void cancelOrder(int id) {
        std::cout << "[LOG] Вызов cancelOrder для заказа " << id << "\n";
        realFacade_.cancelOrder(id);
    }

    void getStatistics() {
        std::cout << "[LOG] Вызов getStatistics\n";
        realFacade_.getStatistics();
    }

    void listProducts() {
        std::cout << "[LOG] Вызов listProducts\n";
        realFacade_.listProducts();
    }

    void listOrders() {
        std::cout << "[LOG] Вызов listOrders\n";
        realFacade_.listOrders();
    }

    void executeCommand(std::shared_ptr<Command> cmd) {
        std::cout << "[LOG] Выполнение команды\n";
        realFacade_.executeCommand(cmd);
    }

    void processInput(const std::string& input) {
        realFacade_.processInput(input);
    }
};
