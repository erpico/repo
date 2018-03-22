#pragma once
#include "AclLib.h"
#include "TaskPriority.h"

class MessengerUser;

class ACLLIB_API ChatMessage
{
private:
	long id;
	long userInId;
	long userOutId;
	long date;
	CString text;
	MessengerUser *userIn;
	MessengerUser *userOut;
public:
	ChatMessage(void);
	~ChatMessage(void);
public:
	long getId() const { return id; }
	void setId(long val) { id = val; }
	long getUserInId() const { return userInId; }
	void setUserInId(long val) { userInId = val; }
	long getUserOutId() const { return userOutId; }
	void setUserOutId(long val) { userOutId = val; }
	MessengerUser * getUserIn() const { return userIn; }
	void setUserIn(MessengerUser * val) { userIn = val; }
	MessengerUser * getUserOut() const { return userOut; }
	void setUserOut(MessengerUser * val) { userOut = val; }
	long getDate() const { return date; }
	void setDate(long val) { date = val; }
	CString getText() const { return text; }
	void setText(CString val) { text = val; }
};

