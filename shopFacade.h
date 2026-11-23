#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "shopMediator.h"
#include <map>

class Command; 
class Handler; 

class ShopFacade {
    Warehouse& warehouse_;
    ShopMediator& mediator_;
    std::shared_ptr<Handler> firstHandler_;

public:
    ShopFacade(Warehouse& w, ShopMediator& m) : warehouse_(w), mediator_(m) {}

    void addProduct(std::unique_ptr<Product> product) { warehouse_.addProduct(std::move(product)); }
    void changePrice(int id, int newPrice) { warehouse_.changePrice(id, newPrice); }
    void changeQuantity(int id, int delta) { warehouse_.changeQuantity(id, delta); }
    void moveProduct(int id, int whId) { warehouse_.moveProduct(id, whId); }
    void removeProduct(int id) { warehouse_.removeProduct(id); }
    void listProducts() { warehouse_.listProducts(); }

    void createOrder(const std::string& customer, const std::map<int, int>& items, const std::string& delivery) {
        mediator_.createOrder(customer, items, delivery);
    }
    void cancelOrder(int id) { mediator_.cancelOrder(id); }
    void confirmPayment(int id) { mediator_.confirmPayment(id); }
    void shipOrder(int id) { mediator_.shipOrder(id); }
    void getStatistics() { mediator_.getStatistics(); }
    void listOrders() { mediator_.listOrders(); }

    void executeCommand(std::shared_ptr<Command> cmd);
    void setHandlers(std::shared_ptr<Handler> first) { firstHandler_ = first; }
    void processInput(const std::string& input);
};