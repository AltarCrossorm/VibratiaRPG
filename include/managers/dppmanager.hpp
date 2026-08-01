#pragma once
#include <coroutine>
#include <dpp/dpp.h>
#include <functional>
#include <dpp/coro/task.h>

using dpp_async = dpp::task<void>;
#define newDPPObject(type, func) [this](const dpp::type& e) -> dpp_async {co_await this->func(e);co_return;}

template<typename T>
using ManagerCallback = std::function<dpp_async(T)>;

class DppManager
{
    virtual void setup(dpp::cluster& bot) = 0;
    virtual void on_ready(dpp::cluster& bot) = 0;
};
