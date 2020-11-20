/*
 * ContactManager
 *
 *
 * Капралов А.
 * 08.11.2013 16:35
 */

#ifndef __CONTACTMANAGER_H__
#define __CONTACTMANAGER_H__

#include "ErpicoPBX.h"

#include "AclLib/AclObjects.h"
#include "ContactObjects.h"
#include "ContactPriest.h"

#include <list>

class ERPICOPBX_API ContactManager {
private:
  const User *user;

private:
  ContactPriest *priest;

public:
  ContactManager();
  virtual ~ContactManager();

public:
  int initialize(const char *serverUrl, const User *user);

public:
  int getContactDetails(std::list<ContactDetail> &result, long &totalCount,
      int firstResult, int maxResults);
  int getContactDetail(ContactDetail &result, long id);
  int createContactDetail(long &id, long contactId, ContactDetailType type, const char * value);
  int updateContactDetail(long id, long contactId, ContactDetailType type, const char * value);
  int deleteContactDetail(long id);

public:
  int getContacts(std::list<Contact> &result, long &totalCount,
      int firstResult, int maxResults, const char *name, const char *detailValue, const char *anyField);
  int getContact(Contact &result, long id);
  int createContact(long &id, long ownerId, const char * firstName, const char * middleName, const char * lastName, 
      const char * note, const std::list<ContactDetail> &details);
  int updateContact(long id, long ownerId, const char * firstName, const char * middleName, const char * lastName, 
      const char * note, const std::list<ContactDetail> &details);
  int deleteContact(long id);

};

#endif // __CONTACTMANAGER_H__