#pragma once

#include "AclLib.h"

class ACLLIB_API ConversationMessage
{
private:
    long id;
    long conversationId;
    long created;
    long participantId;
    CString text;
    long stUserId;
    bool read;
public:
    ConversationMessage(void);
    ~ConversationMessage(void);
public:
    long getId() const { return id; }
    void setId(long val) { id = val; }
    long getConversationId() const { return conversationId; }
    void setConversationId(long val) { conversationId = val; }
    long getCreated() const { return created; }
    void setCreated(long val) { created = val; }
    long getParticipantId() const { return participantId; }
    void setParticipantId(long val) { participantId = val; }
    CString getText() const { return text; }
    void setText(CString val) { text = val; }
    long getStUserId() const { return stUserId; }
    void setStUserId(long val) { stUserId = val; }
    bool isRead() const { return read; }
    void setRead(bool val) { read = val; }
    ConversationMessage & operator=(const ConversationMessage &obj);
};

