/*
 * CallInfo.h
 * 
 *
 * Капралов А.
 * 27.2.2013 18:08
 */

#ifndef __CALLINFO_H__
#define __CALLINFO_H__

#include "ErpicoPBX.h"

#include "AclLib/AclObjects.h"

#include <list>
#include <vector>
#include <map>

class CdrPriest;

enum CallDirection {
  CALL_DIRECTION_UNKNOWN  = 0,
  CALL_DIRECTION_OUTGOING = 1,
  CALL_DIRECTION_INCOMING = 2,
};

enum CallDisposition {
  CALL_DISPOSITION_UNKNOWN    = 0,
  CALL_DISPOSITION_ANSWERED   = 1,
  CALL_DISPOSITION_NO_ANSWER  = 2,
  CALL_DISPOSITION_BUSY       = 3,
  CALL_DISPOSITION_FAILED     = 4,
};

class ERPICOPBX_API Call {
  friend class CdrPriest;
protected:
  long id;
  CTime time;
  CString source;
  CString destination;
  CString contactName;
  CString channel;
  CString destinationChannel;
  CallDisposition disposition;
  int totalDuration;
  int duration;
  CString comment;

public:
  Call();
  virtual ~Call();

public:
  long getId() const;
  void setId(long id);

  const CTime & getTime() const;
  void setTime(const CTime &time);
  void setTime(long time);

  const char * getSource() const;
  void setSource(const char *source);

  const char * getDestination() const;
  void setDestination(const char *destination);

  const char * getContactName() const;
  void setContactName(const char *contactName);

  const char * getChannel() const;
  void setChannel(const char *channel);

  const char * getDestinationChannel() const;
  void setDestinationChannel(const char *destinationChannel);

  CallDisposition getDisposition() const;
  void setDisposition(CallDisposition disposition);

  bool isCompleted() const;
  
  int getTotalDuration() const;
  void setTotalDuration(int totalDuration);

  int getDuration() const;
  void setDuration(int duration);

  const char * getComment() const;
  void setComment(const char *comment);
};

class ERPICOPBX_API CallHelper {
public:
  static CallDirection getDirection(const char *userPhoneNumber, const Call &call);
  static const char * getNumber(const char *userPhoneNumber, const Call &call);
  static const char * getPeer(const char *userPhoneNumber, const Call &call);
  static void parseLine(CString &result, const char *peer);
};

class ERPICOPBX_API CdrManager {
private:
  const User *pUser;

private:
  CdrPriest *pPriest;

public:
  CdrManager();
  virtual ~CdrManager();

public:
  int initialize(const char *serverUrl, const User *pUser);

public:
  int getCalls(std::vector<Call> &result, long &totalCount, int firstResult, int maxResults, 
      const char *number = NULL, const char *secondNumber = NULL,
      time_t timeFrom = 0, time_t timeTo = 0, 
      const char *source = NULL, const char *destination = NULL, 
      const char *contactName = NULL, const char *line = NULL,
      CallDisposition disposition = CALL_DISPOSITION_UNKNOWN);
  int downloadRecordTo(long callId, CString &fileName);
  
};

#endif // __CALLINFO_H__
