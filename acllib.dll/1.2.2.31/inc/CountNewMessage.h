#pragma once
#include "AclLib.h"
#include "MessangerUser.h"
class ACLLIB_API CountNewMessage
{
private:
  int countMessage;
  MessengerUser * user;
  long dateLastSend;
public:
  CountNewMessage(void);
  virtual ~CountNewMessage(void);
public:
  int getCountMessage() const { return countMessage; }
  void setCountMessage(int val) { countMessage = val; }
  MessengerUser * getUser() const { return user; }
  void setUser(MessengerUser * val) { user = val; }
  long getDateLastSend() const { return dateLastSend; }
  void setDateLastSend(long val) { dateLastSend = val; }
};

