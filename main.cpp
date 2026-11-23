#define NOMINMAX 
#include <windows.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include "warehouse.h"
#include "shopMediator.h"
#include "shopFacade.h"
#include "handlers.h"
#include "loggingProxy.h"

void menuAddProduct(LoggingProxy& proxy, ShopFacade& facade) {
    std::cout << "\nВыберите категорию товара\n";
    std::cout << "1. Электроника\n";
    std::cout << "2. Одежда\n";
    std::cout << "3. Еда\n";
    std::cout << "Выбор: ";
    int catChoice;
    if (!(std::cin >> catChoice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }

    std::string type;
    if (catChoice == 1) {
        std::cout << "Выберите тип (1 - Smartphone, 2 - Laptop): ";
        int tc; std::cin >> tc;
        type = (tc == 1) ? "Smartphone" : "Laptop";
    }
    else if (catChoice == 2) {
        std::cout << "Выберите тип (1 - TShirt, 2 - Jacket): ";
        int tc; std::cin >> tc;
        type = (tc == 1) ? "TShirt" : "Jacket";
    }
    else if (catChoice == 3) {
        std::cout << "Выберите тип (1 - Milk, 2 - Bread): ";
        int tc; std::cin >> tc;
        type = (tc == 1) ? "Milk" : "Bread";
    }
    else return;

    std::string name;
    int price, qty;
    std::cout << "Название: "; std::cin >> name;
    std::cout << "Цена: "; std::cin >> price;
    std::cout << "Количество: "; std::cin >> qty;

    auto cmd = std::make_shared<AddProductCommand>(facade, type, name, price, qty);
    proxy.executeCommand(cmd);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Warehouse warehouse;
    OrderManager orderManager;
    PaymentSystem paymentSystem;
    DeliveryService deliveryService;
    ShopMediator mediator(warehouse, orderManager, paymentSystem, deliveryService);
    ShopFacade facade(warehouse, mediator);
    LoggingProxy proxy(facade);

    auto add = std::make_shared<AddProductHandler>(facade);
    auto chPrice = std::make_shared<ChangePriceHandler>(facade);
    auto chQty = std::make_shared<ChangeQuantityHandler>(facade);
    auto move = std::make_shared<MoveProductHandler>(facade);
    auto rem = std::make_shared<RemoveProductHandler>(facade);
    auto createOrd = std::make_shared<CreateOrderHandler>(facade);
    auto cancelOrd = std::make_shared<CancelOrderHandler>(facade);
    auto confPay = std::make_shared<ConfirmPaymentHandler>(facade);
    auto ship = std::make_shared<ShipOrderHandler>(facade);
    auto stat = std::make_shared<ShowStatisticsHandler>(facade);
    auto prod = std::make_shared<ShowProductsHandler>(facade);
    auto ord = std::make_shared<ShowOrdersHandler>(facade);
    auto help = std::make_shared<HelpHandler>(facade);

    add->setNext(chPrice); chPrice->setNext(chQty); chQty->setNext(move);
    move->setNext(rem); rem->setNext(createOrd); createOrd->setNext(cancelOrd);
    cancelOrd->setNext(confPay); confPay->setNext(ship); ship->setNext(stat);
    stat->setNext(prod); prod->setNext(ord); ord->setNext(help);

    facade.setHandlers(add);

    std::cout << "Выберите режим работы:\n";
    std::cout << "1. Меню \n";
    std::cout << "2. Текстовая консоль (демонстрация Цепочки обязанностей)\n";
    std::cout << "Выбор: ";
    int mode;
    std::cin >> mode;

    if (mode == 1) {
        int choice;
        while (true) {
            std::cout << "\nМЕНЮ МАГАЗИНА\n";
            std::cout << "1. Добавить товар\n";
            std::cout << "2. Изменить цену\n";
            std::cout << "3. Изменить остаток\n";
            std::cout << "4. Удалить товар\n";
            std::cout << "5. Показать все товары\n";
            std::cout << "6. Создать заказ\n";
            std::cout << "7. Подтвердить оплату\n";
            std::cout << "8. Отправить заказ\n";
            std::cout << "9. Отменить заказ\n";
            std::cout << "10. Статистика\n";
            std::cout << "11. Показать заказы\n";
            std::cout << "0. Выход\n";
            std::cout << "Выберите действие: ";

            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка ввода.\n";
                continue;
            }
            if (choice == 0) break;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
            case 1: menuAddProduct(proxy, facade); break;
            case 2: {
                int id, price;
                std::cout << "ID товара: "; std::cin >> id;
                std::cout << "Новая цена: "; std::cin >> price;
                proxy.executeCommand(std::make_shared<ChangePriceCommand>(facade, id, price));
                break;
            }
            case 3: {
                int id, delta;
                std::cout << "ID товара: "; std::cin >> id;
                std::cout << "Дельта (например, -2): "; std::cin >> delta;
                proxy.executeCommand(std::make_shared<ChangeQuantityCommand>(facade, id, delta));
                break;
            }
            case 4: {
                int id;
                std::cout << "ID товара: "; std::cin >> id;
                proxy.executeCommand(std::make_shared<RemoveProductCommand>(facade, id));
                break;
            }
            case 5: proxy.listProducts(); break;
            case 6: {
                std::string customer, itemsStr, delivery;
                std::cout << "Имя клиента: "; std::cin >> customer;
                std::cout << "Товары (формат ID:кол-во через запятую, например 1:2,2:1): "; std::cin >> itemsStr;
                std::cout << "Доставка (courier/post/pickup): "; std::cin >> delivery;

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
                proxy.executeCommand(std::make_shared<CreateOrderCommand>(facade, customer, items, delivery));
                break;
            }
            case 7: {
                int id; std::cout << "ID заказа: "; std::cin >> id;
                proxy.executeCommand(std::make_shared<ConfirmPaymentCommand>(facade, id));
                break;
            }
            case 8: {
                int id; std::cout << "ID заказа: "; std::cin >> id;
                proxy.executeCommand(std::make_shared<ShipOrderCommand>(facade, id));
                break;
            }
            case 9: {
                int id; std::cout << "ID заказа: "; std::cin >> id;
                proxy.executeCommand(std::make_shared<CancelOrderCommand>(facade, id));
                break;
            }
            case 10: proxy.getStatistics(); break;
            case 11: proxy.listOrders(); break;
            default: std::cout << "Неверный выбор.\n";
            }
        }
    }
    else if (mode == 2) {
        std::cout << "\nВведите 'help' для списка команд, 'exit' для выхода.\n";
        std::string line;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        while (std::getline(std::cin, line)) {
            if (line == "exit") break;
            if (line.empty()) continue;
            proxy.processInput(line);
        }
    }

    std::cout << "Работа завершена.\n";
    return 0;
}