#pragma once
/**
 * @file messagemanager.hpp
 * @date 2026/07/25
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */
#include "dppmanager.hpp"
#include <vector>
#include <dpp/dpp.h>

#define newMessageCreate(func) newDPPObject(message_create_t,func)

using MessageCreateCallback = ManagerCallback<dpp::message_create_t>;
using MessageDeleteCallback = ManagerCallback<dpp::message_delete_t>;
using MessageDeleteBulkCallback = ManagerCallback<dpp::message_delete_bulk_t>;
using MessageUpdateCallback = ManagerCallback<dpp::message_update_t>;

using MessagePollVoteAddCallback = ManagerCallback<dpp::message_poll_vote_add_t>;
using MessagePollVoteRemoveCallback = ManagerCallback<dpp::message_poll_vote_remove_t>;

using MessageReactionAddCallback = ManagerCallback<dpp::message_reaction_add_t>;
using MessageReactionRemoveCallback = ManagerCallback<dpp::message_reaction_remove_t>;
using MessageReactionRemoveAllCallback = ManagerCallback<dpp::message_reaction_remove_all_t>;
using MessageReactionRemoveEmojiCallback = ManagerCallback<dpp::message_reaction_remove_emoji_t>;



class MessageManager : public DppManager
{
	static MessageManager* inst;
	std::vector<MessageCreateCallback>* createCallbacks;
	std::vector<MessageDeleteCallback>* deleteCallbacks;
	std::vector<MessageDeleteBulkCallback>* deleteBulkCallbacks;
	std::vector<MessageUpdateCallback>* updateCallbacks;

public:
	MessageManager() {
		if(!(this->inst)) this->inst = this;
		this->createCallbacks = new std::vector<MessageCreateCallback>;
		this->deleteCallbacks = new std::vector<MessageDeleteCallback>;
		this->deleteBulkCallbacks = new std::vector<MessageDeleteBulkCallback>;
		this->updateCallbacks = new std::vector<MessageUpdateCallback>;
	}

	~MessageManager() {
		delete this->createCallbacks;
		delete this->deleteCallbacks;
		delete this->deleteBulkCallbacks;
		delete this->updateCallbacks;
	}

	static MessageManager* instance(void);

	void addMessageCreateListener(MessageCreateCallback fn);
	void addMessageDeleteListener(MessageDeleteCallback fn);
	void addMessageDeleteBulkListener(MessageDeleteBulkCallback fn);
	void addMessageUpdateListener(MessageUpdateCallback fn);

	virtual void setup(dpp::cluster& bot) override;
    virtual void on_ready(dpp::cluster& bot) override;

	std::vector<MessageCreateCallback>* getCreateCallbacks(void);
	std::vector<MessageDeleteCallback>* getDeleteCallbacks(void);
	std::vector<MessageDeleteBulkCallback>* getDeleteBulkCallbacks(void);
	std::vector<MessageUpdateCallback>* getUpdateCallbacks(void);
};
