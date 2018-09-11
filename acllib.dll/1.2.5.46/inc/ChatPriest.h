#pragma once

#include "AclLib.h"
#include "ChatResponse.h"

#include "AclObjects.h"
#include "ServerPriest.h"
#include "MessangerUser.h"
#include "ChatMessage.h"
#include "CountNewMessage.h"
#include "ApplicationState.h"
#include "ChatTaskId.h"
#include "PrioritieTaskConverter.h"
#include "ConversationState.h"

class ACLLIB_API ChatPriest :
  public ServerPriest
{
private:
  std::list<MessengerUser *> users;
public:
  ChatPriest(void);
  virtual ~ChatPriest(void);
private:
  int prepareGet—ontactsRequest(CString &request, const User & user);
  int prepareGet—ontactRequest(CString &request, const User &user,CString name);
  
  int prepareSendMessageRequest(CString &request, const User &userTo, CString message,long dateSend,CString authToken);
  int prepareSendTaskRequest(CString &request, const User &userTo, CString message,long dateEnd,TaskPriority prioritieTask, TaskState taskState, CString authToken);
  int prepareUpdateTaskRequest(CString &request, long id, CString message, long dateEnd, TaskPriority taskPriority, TaskState taskState, User * userToSend,const char * authToken );

  int prepareGetMessageRequest(CString &request, User * userTo, User * userFrom, long dateLastUpdate,int firstToEndNumMessage, int countMessage,int unread);
  int prepareGetMessageRequestAsyn(CString &request, long userIdTo,long timestampResive,int firstToEndNumMessage,int countMessage,long startIdMessage,int unread,const char * authToken);
  int prepareGetTaskRequestAsyn(CString &request, long idUserContact,long dateLastUpdate,int firstResult,int maxResults,long startId,int unread,const char * authToken);

  int prepareGetCountNewMessage(CString &request, User * userTo);
  int prepareGetCountNewMessageAsyn(CString &request, const char * authToken, int updateAll);
  int prepareGetCountNewTaskAsyn(CString &requst, const char * authToken, int updateAll);

  int prepareSetMessageToRead(CString &request, User* user, std::list<long> idMessageToRead);
  int prepareSetTaskToRead(CString &request, User* user, std::list<long> idTaskToRead);
  int prepareUpdateStateUser( CString &request, User* user, ApplicationState state );

  //Conversations
  int prepareGetConversations(CString &request, long first, int max, const char * authToken, CString externalUserUid, long stId, long stGroupId,bool * archived, bool assigned);
  int prepareUpdateConversation(CString &request, const char * authToken, long id, long stId, long stGroupId, bool * archived, ConversationState * state);
  int prepareCreateConversationMessage(CString &request, const char * authToken, long conversationId, long stId, CString content);
  int prepareGetConversationMessages(CString &request, const char * authToken, long first, long max, long from, long to);
  int prepareUpdateConversationMessage(CString &request, const char * authToken, long id, bool read);
private:
  int parse—ontactNode(CXMLNode &contactNode, ChatResponse &response);

  int parseCreateMessageNode(CXMLNode &sendTaskNode, ChatResponse &response);
  int parseSendTaskNode(CXMLNode &sendMessageNode, ChatResponse &response);

  int parseGetMessagesNode(CXMLNode &getMessageNode, ChatResponse &response);
  int parseMessageNode(CXMLNode &getMessageNode, long * userIn, long *userOut, long * date, CString * text,long * id );
  int parseGetTaskNode(CXMLNode &getMessageNode, ChatResponse &response);
  int parseTaskNode(CXMLNode &getMessageNode, ChatTaskId &chatTask);

  int parseGetCountNewMessage(CXMLNode &getCountNewMessage, ChatResponse &response );
  int parseCountNewMessageNode(CXMLNode &node, ChatResponse &response);
  int parseGetCountNewTask(CXMLNode &getCountNewMessage, ChatResponse &response );
  int parseCountNewTaskNode(CXMLNode &node, ChatResponse &response);
  int parseSetMessageToRead(CXMLNode &node, ChatResponse &response);
  int parseSetTaskToRead(CXMLNode &node, ChatResponse &response);
  int parseAppicationState(CXMLNode & node, ChatResponse & response);

  //Conversations
  int parseGetConversations(CXMLNode & node, ChatResponse & response);
  int parseUpdateConversation(CXMLNode & node, ChatResponse & response);
  int parseCreateConversationMessage(CXMLNode & node, ChatResponse & response);
  int parseGetConversationMessages(CXMLNode & node, ChatResponse & response);
  int parseUpdateConversationMessage(CXMLNode & node, ChatResponse & response);
private:
  int callService(const CString &request, ServerResponse *pServerResponse);
public:
  int get—ontacts(std::list<MessengerUser *> &result, const User &user);
  int getContact(User &result,const User &user,CString name);
  
  int sendMessage(long &result, User &userTo, CString message,CString authToken);

  int sendTask(User &userTo, CString message, long dateEnd,TaskPriority prioritieTask, TaskState taskState,CString authToken);
  int updateTask(long id, CString message, long dateEnd, TaskPriority taskPriority, TaskState taskState, User * userToSend,const char * authToken );

  int getMessage(std::list<ChatMessage> &result, User * authorizedUser, User * otherUser,long dateLastUpdate,int firstToEndNumMessage, int countMessage,int unread, std::map<long, MessengerUser *> hashedUser);
  int getMessageAsyn(std::list<ChatMessage> &result, long idUserContact,long dateLastUpdate,int firstToEndNumMessage, int countMessage,int unread,const char * authToken);
  int getMessageAsyn(std::list<ChatMessage> &result, long idUserContact,long dateLastUpdate,int firstToEndNumMessage, int countMessage,long startIdMessage,int unread,const char * authToken);

  int getTaskAsyn(std::list<ChatTaskId> &result, long idUserContact, long dateLastUpdate, int firstResult,int maxResults,int startId,int unread,const char * authToken);

  int getCountNewMessage(std::list<CountNewMessage> &countNewMessages, User * authorizedUser, std::map<long, MessengerUser *> hashedUser);
  int getConversationSummaryMessageAsyn(std::list<ConversationSummary> &countNewMessagesId,const char * authToken, int updateAll);

  int getConversationSummaryTaskAsyn(std::list<ConversationSummary> &countNewMessagesId,const char * authToken, int updateAll);

  int setMessageToRead(std::list<long> messageToRead,  User* user);
  int setTaskToRead(std::list<long> taskToRead,  User* user);

  int updateStateUser(ApplicationState state,User* user );

  int prepareSetUserHidden(CString &request, User* user, long id, bool isToHide);
  int setUserHidden(long id, User* user, bool isToHide);

  //Conversations
  int getConversations(std::list<Conversation*> &result, const char * authToken, long first, int max, CString externalUserUid, long stId, long stGroupId,bool * archived, bool assigned);
  int updateConversation(const char * authToken, long id, long stId, long stGroupId, bool * archived, ConversationState * state);
  int createConversationMessage(long &id, const char * authToken, long conversationId, long stId, CString content);
  int getConversationMessages(std::list<ConversationMessage> &result, const char * authToken, long first, long max, long from, long to);
  int updateConversationMessage(const char * authToken, long id, bool read);
  int createConverstation(const char * authToken);
  int getDialogConversationSummaryAsyn(std::list<ConversationSummary> &result,const char * authToken);
  int claimConversation(const char * authToken, int &result, long id, long userId);
private:
  int prepareGetNewConvMessagesCountAsyn(CString &request,const char * authToken);
  int parseNewConvMessageCountNode(CXMLNode &node, ChatResponse &response);
  int parseNewConvMessageCount(CXMLNode &getMessageNode, ChatResponse &response);
  int prepareClaimConversation(CString &request, const char* authToken, long id, long userId);
  int parseClaimConversation(CXMLNode &node, ChatResponse &response);
protected:
  int parseNode(CXMLNode &node, ServerResponse *pServerResponse);
  void addContacts(MessengerUser *user);
};

