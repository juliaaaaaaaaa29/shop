#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>


class ShopFacade; 

class Command {
protected:
    ShopFacade& facade_;
public:
    explicit Command(ShopFacade& facade) : facade_(facade) {}
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class CommandHistory {
    std::vector<std::shared_ptr<Command>> history_;
public:
    void push(std::shared_ptr<Command> cmd);
    std::shared_ptr<Command> getLastCommand();
};

class AddProductCommand : public Command {
    std::string type_, name_;
    int price_, quantity_;
public:
    AddProductCommand(ShopFacade& f, std::string type, std::string name, int price, int quantity);
    void execute() override;
};

class ChangePriceCommand : public Command {
    int productId_, newPrice_;
public:
    ChangePriceCommand(ShopFacade& f, int id, int price);
    void execute() override;
};

class ChangeQuantityCommand : public Command {
    int productId_, delta_;
public:
    ChangeQuantityCommand(ShopFacade& f, int id, int delta);
    void execute() override;
};

class MoveProductCommand : public Command {
    int productId_, newWarehouseId_;
public:
    MoveProductCommand(ShopFacade& f, int id, int whId);
    void execute() override;
};

class RemoveProductCommand : public Command {
    int productId_;
public:
    RemoveProductCommand(ShopFacade& f, int id);
    void execute() override;
};
class CreateOrderCommand : public Command {
    std::string customer_, deliveryType_;
    std::map<int, int> items_;
public:
    CreateOrderCommand(ShopFacade& f, std::string cust, std::map<int, int> items, std::string delivery);

    void execute() override;
};

class CancelOrderCommand : public Command {
    int orderId_;
public:
    CancelOrderCommand(ShopFacade& f, int id);
    void execute() override;
};

class ConfirmPaymentCommand : public Command {
    int orderId_;
public:
    ConfirmPaymentCommand(ShopFacade& f, int id);
    void execute() override;
};

class ShipOrderCommand : public Command {
    int orderId_;
public:
    ShipOrderCommand(ShopFacade& f, int id);
    void execute() override;
};

class ShowStatisticsCommand : public Command {
public:
    ShowStatisticsCommand(ShopFacade& f);
    void execute() override;
};

class ShowProductsCommand : public Command {
public:
    ShowProductsCommand(ShopFacade& f);
    void execute() override;
};

class ShowOrdersCommand : public Command {
public:
    ShowOrdersCommand(ShopFacade& f);
    void execute() override;
};