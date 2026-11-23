#pragma once
#include <string>
#include <memory>
#include <stdexcept>
#include "ProductFactory.h" 

class ProductFactoryManager {
public:
    static std::unique_ptr<Product> create(const std::string& type, const std::string& name, int priceInRub, int quantity) {
        int priceInKop = priceInRub * 100;
        double weight = 150.0;

        if (type == "Smartphone") { SmartphoneFactory f; return f.createProduct(name, priceInKop, quantity, weight); }
        if (type == "Laptop") { LaptopFactory f;     return f.createProduct(name, priceInKop, quantity, weight); }
        if (type == "TShirt") { TShirtFactory f;     return f.createProduct(name, priceInKop, quantity, weight); }
        if (type == "Jacket") { JacketFactory f;     return f.createProduct(name, priceInKop, quantity, weight); }
        if (type == "Milk") { MilkFactory f;         return f.createProduct(name, priceInKop, quantity, weight); }
        if (type == "Bread") { BreadFactory f;       return f.createProduct(name, priceInKop, quantity, weight); }

        throw std::invalid_argument("Неизвестный тип товара: " + type);
    }
};