/*
* ContactObjects
*
*
* Капралов А.
* 08.11.2013 17:29
*/

#ifndef __CONTACTOBJECTS_H__
#define __CONTACTOBJECTS_H__

#include "ErpicoPBX.h"

#include <string>
#include <list>

enum ContactDetailType {
  CONTACT_DETAIL_TYPE_UNKNOWN = 0,
  CONTACT_DETAIL_TYPE_MISC = 1,
  CONTACT_DETAIL_TYPE_PHONE = 2,
  CONTACT_DETAIL_TYPE_MOBILE_PHONE = 3,
  CONTACT_DETAIL_TYPE_EMAIL = 4,
  CONTACT_DETAIL_TYPE_ADDRESS = 5,
  CONTACT_DETAIL_TYPE_COMPANY = 6,
  CONTACT_DETAIL_TYPE_TITLE = 7,
  CONTACT_DETAIL_TYPE_DEPARTAMENT = 8,
  CONTACT_DETAIL_TYPE_ICQ = 9,
  CONTACT_DETAIL_TYPE_LOGIN = 10,
  CONTACT_DETAIL_TYPE_LOGINED = 11,
  CONTACT_DETAIL_TYPE_IP = 12,
  CONTACT_DETAIL_TYPE_VERSION = 13
};

#define CONTACT_DETAIL_TYPE_NAME_MISC "MISC"
#define CONTACT_DETAIL_TYPE_NAME_PHONE "PHONE"
#define CONTACT_DETAIL_TYPE_NAME_MOBILE_PHONE "MOBILE_PHONE"
#define CONTACT_DETAIL_TYPE_NAME_EMAIL "EMAIL"
#define CONTACT_DETAIL_TYPE_NAME_ADDRESS "ADDRESS"
#define CONTACT_DETAIL_TYPE_NAME_COMPANY "COMPANY"
#define CONTACT_DETAIL_TYPE_NAME_TITLE "TITLE"
#define CONTACT_DETAIL_TYPE_NAME_ICQ "ICQ"
#define CONTACT_DETAIL_TYPE_NAME_DEPARTAMENT "DEPARTAMENT"
#define CONTACT_DETAIL_TYPE_NAME_LOGIN "LOGIN"
#define CONTACT_DETAIL_TYPE_NAME_LOGINED "LOGINED"
#define CONTACT_DETAIL_TYPE_NAME_IP "IP"
#define CONTACT_DETAIL_TYPE_NAME_VERSION "VERSION"

class ERPICOPBX_API ContactHelper {
public:
  static ContactDetailType stringToContactDetailType(const char *str);
  static const char * contactDetailTypeToString(ContactDetailType contactDetailType);
};

class ERPICOPBX_API ContactDetail {
private:
  long id;
  long contactId;
  ContactDetailType type;
  std::string value;

public:
  ContactDetail();
  ContactDetail(long id, long contactId, ContactDetailType type, const char *value);
  virtual ~ContactDetail();

public:
  long getId() const;
  void setId(long id);

  long getContactId() const;
  void setContactId(long contactId);

  ContactDetailType getType() const;
  void setType(ContactDetailType type);

  const char * getValue() const;
  void setValue(const char * value);

};

class ERPICOPBX_API Contact {
private:
  long id;
  long ownerId;
  std::string firstName;
  std::string middleName;
  std::string lastName;
  std::string note;
  std::list<ContactDetail> details;

public:
  Contact();
  virtual ~Contact();

public:
  long getId() const;
  void setId(long id);

  long getOwnerId() const;
  void setOwnerId(long ownerId);

  const char * getFirstName() const;
  void setFirstName(const char * firstName);

  const char * getMiddleName() const;
  void setMiddleName(const char * middleName);

  const char * getLastName() const;
  void setLastName(const char * lastName);

  const char * getNote() const;
  void setNote(const char * note);

  const std::list<ContactDetail> & getDetails() const;
  void setDetails(const std::list<ContactDetail> &details);

};


#endif // __CONTACTOBJECTS_H__