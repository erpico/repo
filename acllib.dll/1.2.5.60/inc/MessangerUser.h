#pragma once
#include "AclLib.h"
#include "aclobjects.h"
#include "ApplicationState.h"
//#include "ChatMessageId.h"
//#include "ChatTaskId.h"
#include <map>
#include "ChatMessage.h"

class ChatTaskId;

class ACLLIB_API MessengerUser : public User {
private:
  typedef std::map<long, ChatMessage> IdToMessageMap;
  IdToMessageMap m_messages;

  ChatMessage m_lastMsgAdded;

  std::list<ChatTaskId> * tasks;
  
  int countNewMessage;
  long lastResiveMessageTime;
  long lastResiveTaskTime;

  int countNewTask;

  long lastResiveMessageId;
  long lastResiveTaskId;
  ApplicationState applicationState;
  long stId;
  long stGroupId;
  bool hidden;
  bool bSel;
public:
  MessengerUser(void);
  virtual ~MessengerUser(void);
public:
  
  std::list<ChatTaskId> * getTasks();

  int getMessageCount() const;
  bool AddMessage(const ChatMessage& msg);
  const ChatMessage& GetMessageById(long msgId) const;
  const ChatMessage& GetLastMsgAdded() const;
  
  int getCountNewMessage() const;
  void setCountNewMessage(int val);
  long getLastResiveMessageTime() const;
  void setLastReceivedMessageTime(long val);
  long getLastResiveTaskTime() const;
  void setLastResiveTaskTime(long val);

  int getCountNewTask() const;
  void setCountNewTask(int val);

  long getLastResiveMessageId() const;
  void setLastResiveMessageId(long val);
  long getLastResiveTaskId() const;
  void setLastResiveTaskId(long val);

  ApplicationState getApplicationState() const;
  void setApplicationState(ApplicationState val);
  long getStId() const;
  void setStId(long val);
  long getStGroupId() const;
  void setStGroupId(long val);
  bool isHidden();
  void setHidden(bool val);
  void SetSel(bool _iSel);
  bool GetSel();
};

