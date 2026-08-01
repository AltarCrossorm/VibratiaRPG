#pragma once
/**
 * @file buttonmanager.hpp
 * @date 2026/07/21
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */
#include <string>
#include <map>
#include <utility>
#include <dpp/dpp.h>
#include <type_traits>
#include "dppmanager.hpp"

#define newButton(func) newDPPObject(button_click_t,func)

using ButtonCallback = ManagerCallback<dpp::button_click_t>;

constexpr unsigned int STATELESS_TIMEOUT = 0;

struct ButtonInfo {
	ButtonCallback callback;
	unsigned int timeout; // Timeout in seconds, 0 if stateless
};

class ButtonManager: public DppManager
{
private:
    static ButtonManager* inst;
    std::map<std::string,ButtonInfo>* mapButtons = nullptr;
public:
    ButtonManager() {
        if(!(this->inst)) this->inst = this;
        this->mapButtons = new std::map<std::string,ButtonInfo>;
    }
    ~ButtonManager() {
        delete this->mapButtons;
    }
    
    static ButtonManager* instance(void);
    static void addButton(std::string&& id, ButtonCallback button, unsigned int timeout = 300);

    virtual void setup(dpp::cluster& bot) override;
    virtual void on_ready(dpp::cluster& bot) override;

    std::map<std::string,ButtonInfo>* getMapButtons(void);
};
