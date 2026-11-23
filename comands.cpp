#include "comands.h"
#include "shopFacade.h"
#include "productFactoryManager.h"
#include <iostream>
#include <map>

void CommandHistory::push(std::shared_ptr<Command> cmd) { history_.push_back(cmd); }
std::shared_ptr<Command> CommandHistory::getLastCommand() { return history_.empty() ? nullptr : history_.back(); }

AddProductCommand::AddProductCommand(ShopFacade& f, std::string type, std::string name, int price, int quantity)
    : Command(f), type_(type), name_(name), price_(price), quantity_(quantity) {
}

void AddProductCommand::execute() {
    try {
        auto product = ProductFactoryManager::create(type_, name_, price_, quantity_);
        facade_.addProduct(std::move(product));
    }
    catch (const std::exception& e) {
        std::cerr << "[Îøèáêà] " << e.what() << "\n";
    }
}

ChangePriceCommand::ChangePriceCommand(ShopFacade& f, int id, int price) : Command(f), productId_(id), newPrice_(price) {}
void ChangePriceCommand::execute() { facade_.changePrice(productId_, newPrice_); }

ChangeQuantityCommand::ChangeQuantityCommand(ShopFacade& f, int id, int delta) : Command(f), productId_(id), delta_(delta) {}
void ChangeQuantityCommand::execute() { facade_.changeQuantity(productId_, delta_); }

MoveProductCommand::MoveProductCommand(ShopFacade& f, int id, int whId) : Command(f), productId_(id), newWarehouseId_(whId) {}
void MoveProductCommand::execute() { facade_.moveProduct(productId_, newWarehouseId_); }

RemoveProductCommand::RemoveProductCommand(ShopFacade& f, int id) : Command(f), productId_(id) {}
void RemoveProductCommand::execute() { facade_.removeProduct(productId_); }
CreateOrderCommand::CreateOrderCommand(ShopFacade& f, std::string cust, std::map<int, int> items, std::string delivery)
    : Command(f), customer_(cust), items_(items), deliveryType_(delivery) {
}

void CreateOrderCommand::execute() {
    facade_.createOrder(customer_, items_, deliveryType_);
}
CancelOrderCommand::CancelOrderCommand(ShopFacade& f, int id) : Command(f), orderId_(id) {}
void CancelOrderCommand::execute() { facade_.cancelOrder(orderId_); }

ConfirmPaymentCommand::ConfirmPaymentCommand(ShopFacade& f, int id) : Command(f), orderId_(id) {}
void ConfirmPaymentCommand::execute() { facade_.confirmPayment(orderId_); }

ShipOrderCommand::ShipOrderCommand(ShopFacade& f, int id) : Command(f), orderId_(id) {}
void ShipOrderCommand::execute() { facade_.shipOrder(orderId_); }

ShowStatisticsCommand::ShowStatisticsCommand(ShopFacade& f) : Command(f) {}
void ShowStatisticsCommand::execute() { facade_.getStatistics(); }

ShowProductsCommand::ShowProductsCommand(ShopFacade& f) : Command(f) {}
void ShowProductsCommand::execute() { facade_.listProducts(); }

ShowOrdersCommand::ShowOrdersCommand(ShopFacade& f) : Command(f) {}
void ShowOrdersCommand::execute() { facade_.listOrders(); }