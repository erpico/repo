#pragma once
#include "AclLib.h"
class ACLLIB_API ConversationSummary
{
private:
	int messagesCount;
	long userId; //для диалогов с сайта здесь conversationId 
	long lastMessageTime;

public:
	ConversationSummary(void);
	virtual ~ConversationSummary(void);

public:
	int getMessagesCount() const { return messagesCount; }
	void setMessagesCount(int val) { messagesCount = val; }

	long getUserId() const { return userId; }
	void setUserId(long val) { userId = val; }

	long getMessageTime() const { return lastMessageTime; }
	void setMessageTime(long val) { lastMessageTime = val; }
};

