#pragma once
#include "AclLib.h"
#include "ConversationState.h"
#include "ConversationMessage.h"
#include "ChatTaskId.h"
#include <map>
#include <list>
class ACLLIB_API Conversation
{
private:
  long id;
  CString externalUserUid;
  CString externalUserName;
  long stUserId;
  long stUserGroupId;
  bool archived;
  ConversationState state;
  int countNewMessages;
  long lastSendDate;
  long lastMessageId;
  std::map<long, ConversationMessage> conversationMessages;
  std::list<ConversationMessage> unreadConversationMessages;
public:
  Conversation(void);
  ~Conversation(void);
public:
  long getId() const { return id; }
  void setId(long val) { id = val; }
  CString getExternalUserUid() const { return externalUserUid; }
  void setExternalUserUid(CString val) { externalUserUid = val; }
  CString getExternalUserName() const { return externalUserName; }
  void setExternalUserName(CString val) { externalUserName = val; }
  long getStUserId() const { return stUserId; }
  void setStUserId(long val) { stUserId = val; }
  long getStUserGroupId() const { return stUserGroupId; }
  void setStUserGroupId(long val) { stUserGroupId = val; }
  bool isArchived() const { return archived; }
  void setArchived(bool val) { archived = val; }
  ConversationState getState() const { return state; }
  void setState(ConversationState val) { state = val; }
  int getCountNewMessages() const { return countNewMessages; }
  void setCountNewMessages(int val) { countNewMessages = val; }
  long getLastSendDate() const { return lastSendDate; }
  void setLastSendDate(long val) { lastSendDate = val; }
  long getLastMsgId() const {return lastMessageId;}
  const ConversationMessage &getMsgById(long id);

  const std::map<long, ConversationMessage> & ConversationMessages() const { return conversationMessages; }
  bool updateConversationMessages(const ConversationMessage & conversationMessage);
  bool addConversationMessage(const ConversationMessage & conversationMessage);
  const std::list<ConversationMessage> & getUnreadConversationMessages();
};

