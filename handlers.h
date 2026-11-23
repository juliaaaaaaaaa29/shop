#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include <vector>
#include "comands.h"
#include "shopFacade.h"
#include <map>

class Handler {
protected:
    std::shared_ptr<Handler> next_ = nullptr;
    ShopFacade& facade_;
public:
    Handler(ShopFacade& f) : facade_(f) {}
    virtual ~Handler() = default;

    void setNext(std::shared_ptr<Handler> next) { next_ = next; }

    virtual void handle(const std::string& input) {
        if (next_) {
            next_->handle(input);
        }
        else {
            std::cout << "[Система] Неизвестная команда или неверный синтаксис: " << input << "\n";
        }
    }

};

class AddProductHandler : public Handler {
public:
    AddProductHandler(ShopFacade& f);
    void handle(const std::string& input) override;
};

class ChangePriceHandler : public Handler {
public:
    ChangePriceHandler(ShopFacade& f);
    void handle(const std::string& input) override;
};

class ChangeQuantityHandler : public Handler {
public:
    ChangeQuantityHandler(ShopFacade& f);
    void handle(const std::string& input) override;
};

class MoveProductHandler : public Handler {
public:
    MoveProductHandler(ShopFacade& f);
    void handle(const std::string& input) override;
};

class RemoveProductHandler : public Handler {
public:
    RemoveProductHandler(ShopFacade& f);
    void handle(const std::string& input) override;
};

class CreateOrderHandler : public Handler {
public:
    CreateOrderHandler(ShopFacade& f);
    void handle(const std::string& input) override;
};

class CancelOrderHandler : public Handler {
public:
    CancelOrderHandler(ShopFacade& f);
    void handle(const std::string& input) override;
};

class ConfirmPaymentHandler : public Handler {
public:
    ConfirmPaymentHandler(ShopFacade& f);
    void handle(const std::string& input) override;
};

class ShipOrderHandler : public Handler {
public:
    ShipOrderHandler(ShopFacade& f);
    void handle(const std::string& input) override;
};

class ShowStatisticsHandler : public Handler {
public:
    ShowStatisticsHandler(ShopFacade& f);
    void handle(const std::string& input) override;
};

class ShowProductsHandler : public Handler {
public:
    ShowProductsHandler(ShopFacade& f);
    void handle(const std::string& input) override;
};

class ShowOrdersHandler : public Handler {
public:
    ShowOrdersHandler(ShopFacade& f);
    void handle(const std::string& input) override;
};

class HelpHandler : public Handler {
public:
    HelpHandler(ShopFacade& f);
    void handle(const std::string& input) override;
};