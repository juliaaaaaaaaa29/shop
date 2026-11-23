#pragma once
#include <map>
#include <memory>
#include <iostream>
#include "Product.h"

class Warehouse {
    std::map<int, std::unique_ptr<Product>> products;
public:
    void addProduct(std::unique_ptr<Product> product) {
        if (!product) return;
        int id = product->getId();
        products[id] = std::move(product);
        std::cout << "[Склад] Товар добавлен. ID: " << id << "\n";
    }

    void removeProduct(int id) {
        if (products.erase(id)) std::cout << "[Склад] Товар " << id << " удален.\n";
        else std::cout << "[Ошибка] Товар не найден.\n";
    }

    void changePrice(int id, int newPriceInRub) {
        if (products.count(id)) {
            products[id]->setPrice(Price(newPriceInRub * 100));
            std::cout << "[Склад] Цена обновлена.\n";
        }
        else {
            std::cout << "[Ошибка] Товар не найден.\n";
        }
    }

    void changeQuantity(int id, int delta) {
        if (products.count(id)) {
            products[id]->changeQuantity(delta);
            std::cout << "[Склад] Остаток обновлен.\n";
        }
        else {
            std::cout << "[Ошибка] Товар не найден.\n";
        }
    }

    void moveProduct(int id, int newWarehouseId) {
        std::cout << "[Склад] Товар " << id << " перемещен на склад " << newWarehouseId << "\n";
    }

    Product* findById(int id) {
        auto it = products.find(id);
        return (it != products.end()) ? it->second.get() : nullptr;
    }

    void listProducts() const {
        std::cout << "Товары на складе\n";
        if (products.empty()) {
            std::cout << "Склад пуст.\n";
            return;
        }

        for (auto it = products.begin(); it != products.end(); ++it) {
            it->second->describe();
        }
    }

    double getProductPrice(int id) const {
        auto it = products.find(id);
        if (it != products.end()) {
            return it->second->getPrice().asRubles();
        }
        return 0.0;
    }

    size_t size() const { return products.size(); }
};
