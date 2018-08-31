#pragma once
#include "AclLib.h"
#include "serverpriest.h"
#include "MessangerUser.h"
#include "ChatMessage.h"
#include "CountNewMessageId.h"
#include "ChatTaskId.h"
#include "Conversation.h"
#include "ConversationMessage.h"
class ACLLIB_API ChatResponse : public ServerResponse
{
public:
  ChatResponse(void);
  ~ChatResponse(void);
private:
  std::list<MessengerUser *> contacts;
  std::list<ChatMessage *> messages;
  std::list<ConversationSummary *> countNewMessageId;
  std::list<ChatTaskId> tasks;
  std::list<Conversation*> conversations;
  std::list<ConversationMessage> conversationMessages;
  long lastMessageId;
  long lastConvMessageId;
  int claimConvResult;
public:
  const std::list<MessengerUser *> & get—ontacts() const;
  const std::list<ChatMessage *> & getMessages() const;
  const std::list<ConversationSummary *> & getCountNewMessageId() const;
  std::list<ChatTaskId> & getTasks();
  const std::list<Conversation*> & getConversations() const {return conversations;}
  const std::list<ConversationMessage> & getConversationMessages() const {return conversationMessages;}
  const long getLastMessageId() const {return lastMessageId;}
  const long getLastConvMessageId() const {return lastConvMessageId;}
  const int getClaimConvResult() const {return claimConvResult;}
public:
  void add—ontact(MessengerUser *user);
  void addMessage(ChatMessage *message);
  void addCountNewMessage(ConversationSummary *countNewMessage);
  void addTask(ChatTaskId &chatTaskId);
  void addConversation(Conversation* conversation);
  void addConversationMessage(ConversationMessage &conversationMessage);
  void setLastMessageId(long val) {lastMessageId = val;}
  void setLastConvMessageId(long val) {lastConvMessageId = val;}
  void setClaimConvResult(int val) {claimConvResult = val;}
};

