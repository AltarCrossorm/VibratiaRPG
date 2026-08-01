#include "managers/messagemanager.hpp"
#include <dispatcher.h>
/**
 * @file messagemanager.cpp
 * @date 2026/07/26
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */


MessageManager* MessageManager::inst = nullptr;
MessageManager* MessageManager::instance(void) {
	return inst;
}


void MessageManager::addMessageCreateListener(MessageCreateCallback fn) {
	this->createCallbacks->push_back(fn);
}

void MessageManager::addMessageDeleteListener(MessageDeleteCallback fn) {
	this->deleteCallbacks->push_back(fn);
}

void MessageManager::addMessageDeleteBulkListener(MessageDeleteBulkCallback fn) {
	this->deleteBulkCallbacks->push_back(fn);
}

void MessageManager::addMessageUpdateListener(MessageUpdateCallback fn) {
	this->updateCallbacks->push_back(fn);
}

void MessageManager::setup(dpp::cluster& bot) {
	bot.on_message_create([](const dpp::message_create_t event) -> dpp_async {
		for(const auto& callback : *(MessageManager::instance()->getCreateCallbacks())) {
			co_await callback(event);
		}
		co_return;
	});

	bot.on_message_delete([](const dpp::message_delete_t event) -> dpp_async {
		for(const auto& callback : *(MessageManager::instance()->getDeleteCallbacks())) {
			co_await callback(event);
		}
		co_return;
	});

	bot.on_message_delete_bulk([](const dpp::message_delete_bulk_t event) -> dpp_async {
		for(const auto& callback : *(MessageManager::instance()->getDeleteBulkCallbacks())) {
			co_await callback(event);
		}
		co_return;
	});

	bot.on_message_update([](const dpp::message_update_t event) -> dpp_async {
		for(const auto& callback : *(MessageManager::instance()->getUpdateCallbacks())) {
			co_await callback(event);
		}
		co_return;
	});
}

void MessageManager::on_ready(dpp::cluster&) {
	// Empty function?
}

std::vector<MessageCreateCallback>* MessageManager::getCreateCallbacks(void) {
	return this->createCallbacks;
}

std::vector<MessageDeleteCallback>* MessageManager::getDeleteCallbacks(void) {
	return this->deleteCallbacks;
}

std::vector<MessageDeleteBulkCallback>* MessageManager::getDeleteBulkCallbacks(void) {
	return this->deleteBulkCallbacks;
}

std::vector<MessageUpdateCallback>* MessageManager::getUpdateCallbacks(void) {
	return this->updateCallbacks;
}
