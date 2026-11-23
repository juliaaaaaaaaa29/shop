#include "handlers.h"

AddProductHandler::AddProductHandler(ShopFacade& f) : Handler(f) {}
void AddProductHandler::handle(const std::string& input) {
    std::istringstream iss(input);
    std::string cmd1, cmd2, type, name;
    int price, qty;
    if (iss >> cmd1 >> cmd2 >> type >> name >> price >> qty) {
        if (cmd1 == "add" && cmd2 == "product") {
            facade_.executeCommand(std::make_shared<AddProductCommand>(facade_, type, name, price, qty));
            return;
        }
    }
    if (next_) next_->handle(input);
}

ChangePriceHandler::ChangePriceHandler(ShopFacade& f) : Handler(f) {}
void ChangePriceHandler::handle(const std::string& input) {
    std::istringstream iss(input);
    std::string cmd1, cmd2;
    int id, price;
    if (iss >> cmd1 >> cmd2 >> id >> price) {
        if (cmd1 == "change" && cmd2 == "price") {
            facade_.executeCommand(std::make_shared<ChangePriceCommand>(facade_, id, price));
            return;
        }
    }
    if (next_) next_->handle(input);
}

ChangeQuantityHandler::ChangeQuantityHandler(ShopFacade& f) : Handler(f) {}
void ChangeQuantityHandler::handle(const std::string& input) {
    std::istringstream iss(input);
    std::string cmd1, cmd2;
    int id, delta;
    if (iss >> cmd1 >> cmd2 >> id >> delta) {
        if (cmd1 == "change" && cmd2 == "quantity") {
            facade_.executeCommand(std::make_shared<ChangeQuantityCommand>(facade_, id, delta));
            return;
        }
    }
    if (next_) next_->handle(input);
}

MoveProductHandler::MoveProductHandler(ShopFacade& f) : Handler(f) {}
void MoveProductHandler::handle(const std::string& input) {
    std::istringstream iss(input);
    std::string cmd1, cmd2, cmd3;
    int id, whId;
    if (iss >> cmd1 >> cmd2 >> id >> cmd3 >> whId) {
        if (cmd1 == "move" && cmd2 == "product" && cmd3 == "to") {
            facade_.executeCommand(std::make_shared<MoveProductCommand>(facade_, id, whId));
            return;
        }
    }
    if (next_) next_->handle(input);
}

RemoveProductHandler::RemoveProductHandler(ShopFacade& f) : Handler(f) {}
void RemoveProductHandler::handle(const std::string& input) {
    std::istringstream iss(input);
    std::string cmd1, cmd2;
    int id;
    if (iss >> cmd1 >> cmd2 >> id) {
        if (cmd1 == "remove" && cmd2 == "product") {
            facade_.executeCommand(std::make_shared<RemoveProductCommand>(facade_, id));
            return;
        }
    }
    if (next_) next_->handle(input);
}

CreateOrderHandler::CreateOrderHandler(ShopFacade& f) : Handler(f) {}
void CreateOrderHandler::handle(const std::string& input) {
    std::istringstream iss(input);
    std::string cmd1, cmd2, customer, itemsStr, deliveryType;

    if (iss >> cmd1 >> cmd2 >> customer >> itemsStr >> deliveryType) {
        if (cmd1 == "create" && cmd2 == "order") {
            std::map<int, int> items;
            std::stringstream ss(itemsStr);
            std::string item;

            while (std::getline(ss, item, ',')) {
                size_t colon = item.find(':');
                if (colon != std::string::npos) {
                    int id = std::stoi(item.substr(0, colon));
                    int qty = std::stoi(item.substr(colon + 1));
                    items[id] = qty; 
                }
            }

            facade_.executeCommand(std::make_shared<CreateOrderCommand>(facade_, customer, items, deliveryType));
            return;
        }
    }
    if (next_) next_->handle(input);
}
CancelOrderHandler::CancelOrderHandler(ShopFacade& f) : Handler(f) {}
void CancelOrderHandler::handle(const std::string& input) {
    std::istringstream iss(input);
    std::string cmd1, cmd2;
    int id;
    if (iss >> cmd1 >> cmd2 >> id) {
        if (cmd1 == "cancel" && cmd2 == "order") {
            facade_.executeCommand(std::make_shared<CancelOrderCommand>(facade_, id));
            return;
        }
    }
    if (next_) next_->handle(input);
}

ConfirmPaymentHandler::ConfirmPaymentHandler(ShopFacade& f) : Handler(f) {}
void ConfirmPaymentHandler::handle(const std::string& input) {
    std::istringstream iss(input);
    std::string cmd1, cmd2;
    int id;
    if (iss >> cmd1 >> cmd2 >> id) {
        if (cmd1 == "confirm" && cmd2 == "payment") {
            facade_.executeCommand(std::make_shared<ConfirmPaymentCommand>(facade_, id));
            return;
        }
    }
    if (next_) next_->handle(input);
}

ShipOrderHandler::ShipOrderHandler(ShopFacade& f) : Handler(f) {}
void ShipOrderHandler::handle(const std::string& input) {
    std::istringstream iss(input);
    std::string cmd1, cmd2;
    int id;
    if (iss >> cmd1 >> cmd2 >> id) {
        if (cmd1 == "ship" && cmd2 == "order") {
            facade_.executeCommand(std::make_shared<ShipOrderCommand>(facade_, id));
            return;
        }
    }
    if (next_) next_->handle(input);
}

ShowStatisticsHandler::ShowStatisticsHandler(ShopFacade& f) : Handler(f) {}
void ShowStatisticsHandler::handle(const std::string& input) {
    if (input == "show statistics") {
        facade_.executeCommand(std::make_shared<ShowStatisticsCommand>(facade_));
        return;
    }
    if (next_) next_->handle(input);
}

ShowProductsHandler::ShowProductsHandler(ShopFacade& f) : Handler(f) {}
void ShowProductsHandler::handle(const std::string& input) {
    if (input == "show products") {
        facade_.executeCommand(std::make_shared<ShowProductsCommand>(facade_));
        return;
    }
    if (next_) next_->handle(input);
}

ShowOrdersHandler::ShowOrdersHandler(ShopFacade& f) : Handler(f) {}
void ShowOrdersHandler::handle(const std::string& input) {
    if (input == "show orders") {
        facade_.executeCommand(std::make_shared<ShowOrdersCommand>(facade_));
        return;
    }
    if (next_) next_->handle(input);
}

HelpHandler::HelpHandler(ShopFacade& f) : Handler(f) {}
void HelpHandler::handle(const std::string& input) {
    if (input == "help") {
        std::cout << "Доступные команды:\n"
            << "  add product <type> <name> <price> <qty>\n"
            << "  change price <id> <newPrice>\n"
            << "  change quantity <id> <delta>\n"
            << "  move product <id> to <whId>\n"
            << "  remove product <id>\n"
            << "  create order <customer> <items> <deliveryType>\n"
            << "  cancel order <id>\n"
            << "  confirm payment <id>\n"
            << "  ship order <id>\n"
            << "  show statistics\n"
            << "  show products\n"
            << "  show orders\n";
        return;
    }
    if (next_) next_->handle(input);
}