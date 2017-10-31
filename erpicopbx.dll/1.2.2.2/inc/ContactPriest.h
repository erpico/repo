/*
 * ContactPriest
 *
 *
 * Капралов А.
 * 08.11.2013 18:27
 */

#ifndef __CONTACTPRIEST_H__
#define __CONTACTPRIEST_H__

#include "ErpicoPBX.h"

#include "AclLib/ServerPriest.h"
#include "AclLib/AclObjects.h"
#include "Core/MyXML.h"
#include "ContactObjects.h"

#include <list>

class ERPICOPBX_API ContactServerResponse : public ServerResponse {
  friend class ContactPriest;

private:
  std::list<ContactDetail *> contactDetails;
  std::list<Contact *> contacts;

  long totalCount;

  CString result;

public:
  ContactServerResponse();
  virtual ~ContactServerResponse();

public:
  const std::list<ContactDetail *> & getContactDetails() const;
  const std::list<Contact *> & getContacts() const;

  long getTotalCount();

  const char * getResult();

protected:
  void addContactDetail(ContactDetail *contactDetail);
  void addContact(Contact *contact);

  void setTotalCount(long totalCount);

  void setResult(const char *result);

};

class ERPICOPBX_API ContactPriest : public ServerPriest {
public:
  ContactPriest();
  virtual ~ContactPriest();

private:
  int callService(const CString &request, ServerResponse *serverResponse);

private:
  int prepareGetContactDetailsRequest(CString &request, const User &user, int firstResult, int maxResults);
  int prepareGetContactDetailRequest(CString &request, const User &user, long id);
  int prepareCreateContactDetailRequest(CString &request, const User &user, long contactId, ContactDetailType type, const char * value);
  int prepareUpdateContactDetailRequest(CString &request, const User &user, long id, long contactId, ContactDetailType type, const char * value);
  int prepareDeleteContactDetailRequest(CString &request, const User &user, long id);

private:
  int prepareGetContactsRequest(CString &request, const User &user, int firstResult, int maxResults, 
      const char *name, const char *detailValue, const char *anyField);
  int prepareGetContactRequest(CString &request, const User &user, long id);
  int prepareCreateContactRequest(CString &request, const User &user, long ownerId, 
      const char * firstName, const char * middleName, const char * lastName, const char * note, 
      const std::list<ContactDetail> &details);
  int prepareUpdateContactRequest(CString &request, const User &user, long id, long ownerId, 
      const char * firstName, const char * middleName, const char * lastName, const char * note, 
      const std::list<ContactDetail> &details);
  int prepareDeleteContactRequest(CString &request, const User &user, long id);


protected:
  virtual int parseNode(CXMLNode &node, ServerResponse *serverResponse);

private:
  int parseContactDetailsNode(CXMLNode &ContactDetailsNode, ContactServerResponse &response);
  int parseContactDetailNode(CXMLNode &ContactDetailNode, ContactServerResponse &response);
  int parseContactDetailsNode(CXMLNode &ContactDetailsNode, Contact &contact);
  int parseContactDetailNode(CXMLNode &ContactDetailNode, ContactDetail &contactDetail);

private:
  int parseContactsNode(CXMLNode &ContactsNode, ContactServerResponse &response);
  int parseContactNode(CXMLNode &ContactNode, ContactServerResponse &response);


public:
  int getContactDetails(const User &user, std::list<ContactDetail> &result, long &totalCount, int firstResult, int maxResults);
  int getContactDetail(const User &user, ContactDetail &result, long id);
  int createContactDetail(const User &user, long &id, long contactId, ContactDetailType type, const char * value);
  int updateContactDetail(const User &user, long id, long contactId, ContactDetailType type, const char * value);
  int deleteContactDetail(const User &user, long id);

public:
  int getContacts(const User &user, std::list<Contact> &result, long &totalCount, int firstResult, int maxResults, 
      const char *name, const char *detailValue, const char *anyField);
  int getContact(const User &user, Contact &result, long id);
  int createContact(const User &user, long &id, long ownerId, const char * firstName, const char * middleName, 
      const char * lastName, const char * note, const std::list<ContactDetail> &details);
  int updateContact(const User &user, long id, long ownerId, const char * firstName, const char * middleName, 
      const char * lastName, const char * note, const std::list<ContactDetail> &details);
  int deleteContact(const User &user, long id);


};

#endif // __CONTACTPRIEST_H__