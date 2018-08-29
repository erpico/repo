#pragma once

#include <afxtempl.h>
#include "Core.h"

class CORE_API CUser
{
public:
  typedef struct tagCachedUsernames {
  char user[64];
  char fullName[128];
  char description[128];
  tagCachedUsernames() {
    memset(this, 0, sizeof(*this));
  }  
} CACHED_USERNAMES;

  enum eCategory {
    CAT_OPERATOR = 1,
    CAT_MANAGER  = 2,
  };
typedef struct tagUser {
  char user[64];
  char fullName[128];
  char description[128];
  char email[128];
  bool bDisabled;
  eCategory nCategory;
  tagUser() {
    memset(this, 0, sizeof(*this));
  }
} USER_INFO;

typedef enum tagUserStates {
  USTATE_UNKNOW_ERROR = 0x00,
  USTATE_WORK = 0x01,
  USTATE_LOGOFF,
  USTATE_AWAY,
  USTATE_TMPAWAY
} USER_STATE;

typedef enum eNoticeType {
  NOTICETYPE_UNKNOW       = 0x00,
  NOTICETYPE_ORDER_OFFICE = 0x01
} eNoticeType;

typedef enum eObjectTypes {
  NOTICEOBJTYPE_NONE   = 0x00,
  NOTICEOBJTYPE_ORDER  = 0x01
} eObjectTypes;

  struct sMessage {
    DWORD dwId;
    int nState;
    int nType;
    DWORD dwTime;
    std::string strTime;
    std::string strFrom;
    std::string strMessage;
    sMessage() {
      dwId = 0;
      nState = 0;
      nType = 0;
      dwTime = 0;
      strFrom = "";
      strMessage = "";
    }
  };

  struct sUserStateInfo {
    std::string strUser;
    DWORD tmLogin;
    DWORD tmLogout;
    DWORD tmState;
    USER_STATE nState;
    std::string strPc;
    std::string strAwayComment;
    sUserStateInfo() {
      tmLogin = 0;
      tmLogout = 0;
      tmState = 0;
      nState = USTATE_UNKNOW_ERROR;
    };
  };
  CUser(void);
  ~CUser(void);
  bool Auth();
  std::string m_strLoginName;
  std::string m_strFullName;
  std::string m_strDomain;
  std::string m_strComputer;
  std::string m_strDomainController;
  USER_INFO m_userInfo;

  BOOL m_bSupervisor;

  char ** m_arrGroups;
  DWORD m_nGroups;

  bool IsUserInGroup(const char * group);

  void GetFullUserName(const char* user, char* dest, size_t destSize, char* description = 0, size_t descriptionSize = 0);
  std::string GetFullUserName(const char* user, char* strDescription = 0);

  static USER_STATE GetUserState(const char * user, char* pPCName = 0);
  static std::string GetUSName(USER_STATE state);
  int GetUsersInGroup(const char* strGroup, USER_INFO*& pArr, DWORD* dwCount, int nAsc = 0);
  
  int SessionLogLogin(bool isNewDay = false);
  int SessionLogLogoff(DWORD dwSession = 0);
  int SessionLogStartAway(const char* strComment = 0);
  int SessionLogEndAway(const char* strComment = 0);

  int AgentSessionLogin(bool overrideIfExists = false);
  int AgentSessionLogoff();  
  int AgentSessionStartAway(const char* strComment = 0);
  int AgentSessionEndAway(const char* strComment = 0);
  int AgentSessionCheck();
  int AgentsSessionsCheckFix();

  int AgentGetMessage(sMessage* pMess);
  int AgentGetStateInfo(sUserStateInfo* pInfo);

  static bool AddLocalUser(const char* userName, const char* password, const char *Domain = NULL);
  static bool AddLocalGroup(const char* groupName, const char *Domain = NULL);
  static bool AddLocalUserToGroup(char* userName, char* groupName, bool createUserIfNotFound = true,
                                   bool createGroupIfNotFound = true, const char *Domain = NULL);

  DWORD m_dwSession;
  DWORD m_dwAway;  

  static const char* AgentGetStateName(USER_STATE nState) {
    switch (nState) {
      case USTATE_WORK: return "Работает"; break;
      case USTATE_LOGOFF: return "Не работает"; break;
      case USTATE_AWAY: return "Отсутствует"; break;
      case USTATE_TMPAWAY: return "Временно отсутствует"; break;
    }
    return "Unknown";
  }

  int SendMessage(const char* strTo, CUser::sMessage* pMess);
  BOOL GetUserInfo(const char *UserName, const char *Domain, CUser::USER_INFO *dest);
  int GetMessagesHistory(const char* withUser, CUser::sMessage* arrMessages, int nCount);
  int MessageSetReaded(CUser::sMessage* pMess);
  CArray<CACHED_USERNAMES> m_FNCache;

  int HistoryAddEvent(CUser::eNoticeType eType, const char* strComment, CUser::eObjectTypes eObjType = CUser::NOTICEOBJTYPE_NONE, DWORD dwObjId = 0);
  static int HistoryAddEvent(const char *userName, CUser::eNoticeType eType, const char* strComment, CUser::eObjectTypes eObjType = CUser::NOTICEOBJTYPE_NONE, DWORD dwObjId = 0);
};

CORE_API BOOL GetCurrentUserAndDomain(PTSTR szUser, PDWORD pcchUser, PTSTR szDomain, PDWORD pcchDomain);
<<<<<<< HEAD
CORE_API BOOL GetFullUserNameFromDomain(PTSTR szUser, PTSTR szDomain, std::string & strFullName, std::string & strEmail, std::string & strPhone, std::string & strDescription, std::string & strHomePage, std::string & strGroup, std::string & strTitle);
=======
CORE_API BOOL GetFullUserNameFromDomain(PTSTR szUser, PTSTR szDomain, std::string & strFullName, std::string & strEmail, std::string & strPhone, std::string & strDescription, std::string & strHomePage, std::string & strGroup);
>>>>>>> 89c176ae9dc5e0f157e44d4fb8e5c5415b64b90e
