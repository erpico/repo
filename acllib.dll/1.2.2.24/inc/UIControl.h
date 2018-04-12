#pragma once

#include "AclLib.h"
#include "MessangerUser.h"
#include "ContactSortField.h"
#include "MessageType.h"
#include "Conversation.h"

class ACLLIB_API ControlStateUI
{
private:
  ContactSortField contactSortField;
  MessageType messageType;
  MessengerUser * messengerUser;
  Conversation* conversation;
  bool setMessageToRead;
public:
  ControlStateUI(void);
  virtual ~ControlStateUI(void);
public:
  ContactSortField getContactSortField() const;
  void setContactSortField(ContactSortField val);
  MessageType getMessageType() const;
  void setMessageType(MessageType val);
  MessengerUser * getMessengerUser() const;
  void setMessengerUser(MessengerUser * val);
  Conversation* getConversation() const {return conversation;}
  void setConversation(Conversation* val) {conversation = val;}
  bool getSetMessageToRead() const { return setMessageToRead; }
  void setSetMessageToRead(bool val) { setMessageToRead = val; }
};

