#include "shopFacade.h"
#include "handlers.h" 
#include "comands.h"

void ShopFacade::executeCommand(std::shared_ptr<Command> cmd) {
    if (cmd) {
        cmd->execute(); 
    }
}

void ShopFacade::processInput(const std::string& input) {
    if (firstHandler_) {
        firstHandler_->handle(input);
    }
    else {
        std::cout << "[Ошибка] Цепочка обработчиков не настроена!\n";
    }
}