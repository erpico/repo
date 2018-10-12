#pragma once
//*****#include "AclLib.h"
#include "AclObjects.h"
#include "ChatPriest.h"
#include "ChatTaskId.h"
#include "UIControl.h"
#include "TaskPriority.h"
#include "ConversationState.h"
#include "Conversation.h"

class MessengerUser;

class ACLLIB_API ChatManager {
private:
  bool updatedUser;
  MessengerUser *user;
  ControlStateUI uIControl;
private:
  std::list<MessengerUser *> contact;
  std::map<CString, MessengerUser *> contactNameMap;
  std::map<long, MessengerUser *> contactIdMap;
  std::map<long, Conversation*> conversationMap;
private:
  ChatPriest *chatPriest;
public:
  ChatManager(void);
  virtual ~ChatManager(void);
public:
  int initialize(const char *serverUrl,const User *pUser);
public:
  ControlStateUI * getUIControl() { return &uIControl; }
  MessengerUser * getUser() {
    return user;
  }

  int loadContact();
  std::list<MessengerUser *> loadContactAsyn(const char * authToken);
  void addContact(MessengerUser * user);
  void deleteContact(MessengerUser * user);

  MessengerUser *getCachedContact(const char *name);
  MessengerUser *getCachedContact(long id);
  std::map<long, MessengerUser*> getCachedContacts();

  int getContact(User &result, const char *name, bool cached = true);
  std::list<MessengerUser *> getContacts() {
    return contact;
  }

  std::list<ChatMessage> loadMessage(MessengerUser * user,long dateLastUpdate,int firstToEndNumMessage, int countMessage,int unread);

  std::list<ChatMessage> loadMessageAsyn(long idUserContact,long dateLastUpdate,int firstToEndNumMessage, int countMessage,long startIdMessage,int unread,const char * authToken);
  //std::list<ChatMessage> convertMessageAsyn(std::list<ChatMessageId> &messages);
  void addMessageToUserAsyn(std::list<ChatMessage> &messages,
                            bool checkBeforeAdding, 
                            MessengerUser * userToAddMessage,
                            std::list<ChatMessage>* pMessagesAdded = NULL);

  void addMessagesToUser(std::list<ChatMessage> &messages);

  std::list<ChatTaskId> loadTaskAsys(long idUserContact,long dateLastUpdate,int firstToEndNumMessage, int countMessage,long startIdMessage,int unread,const char * authToken);
  //std::list<ChatTaskId> convertTaskAsyn(std::list<ChatTaskId> &taskId);
  std::list<ChatTaskId> addTaskToUserAsyn(std::list<ChatTaskId> &taskId,bool checkBeforeAdding, MessengerUser * userToAddTask);
  void updateTaskToUserAsyn(std::list<ChatTaskId> * chatTaskId,MessengerUser * userToAddTask);
  void addTaskToUser(std::list<ChatTaskId> &tasks);

  std::list<CountNewMessage> getCountNewMessage();
  std::list<ConversationSummary> getCountNewMessageAsyn(const char * authToken);
  std::list<ConversationSummary> getCountNewMessageAsyn(const char * authToken,int updateAll);
  void addCountNewMessagesToUser(std::list<ConversationSummary> &countNewMessageId);

  std::list<ConversationSummary> getCountNewTaskAsyn(const char * authToken);
  void addCountNewTaskToUser(std::list<ConversationSummary> &countNewMessageId);

  void setMessagesAsRead(std::list<long> idMessageToRead);
  void setMessagesAsReadAsyn(const std::list<long>& messageToRead, long idAuthorizedUser);
  void setMessageAsReadAsyn(long msgId, long idAuthorizedUser);

  void setTaskToReadAsyn(std::list<ChatTaskId> messageToRead, long idAuthorizedUser);

  int sendMessage(long &id, CString message, User * userToSend);
  int sendTask(CString message, long dateEnd,TaskPriority prioritieTask, TaskState taskState, User * userToSend);

  int updateTask(long id,CString message, long dateEnd, TaskPriority taskPriority, TaskState taskState, User * userToSend );

  int updateStateUser( ApplicationState state );

  int getAllCountNewMessage();
  int getAllCountNewTask();
  void GetUnreadCount(int &message,int &task);
  int setUserHidden(long id, bool isToHide); 

  //Conversations
  int getConversations(std::list<Conversation*> &result, CString externalUserUid,/* long stId,*/ long stGroupId,bool * archived, bool assigned);
  int updateConversation(long id, long stId, long stGroupId, bool * archived, ConversationState * state);
  int createConversationMessage(long &result, long conversationId, long stId, const CString &content);
  int createConversationMessage(long &result, long conversationId, const CString &content);
  int getConversationMessages(std::list<ConversationMessage> &result, long from, long to);
  int updateConversationMessages(long id, bool read);
  void addConversation(Conversation* conv);
  void getCachedConversations(std::map<long, Conversation*> &convMap);
  Conversation* getCachedConversation(long id);
  bool equals(Conversation &conversation1, Conversation &conversation2);
  int createConversation();
  std::list<ConversationSummary> getNewConvMessagesCountAsyn(const char * authToken);
  void updateNewConvMessagesCount(std::list<ConversationSummary>& convSummary);
  void addMessagesToConversations(std::list<ConversationMessage> &messages, std::list<ConversationMessage>* messagesAdded = NULL);
  void deleteConversation(long id);
  void resetConversationsCache() {conversationMap.clear();};
  int claimConversation(int &result, long id);
};
