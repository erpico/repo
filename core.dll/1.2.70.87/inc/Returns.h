/************************************************************************
 *  created:    8.4.2008  16:14
 *  filename:   Returns.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __RETURNS_H__
#define __RETURNS_H__

enum EReturnValue {
  // 
  R_OK                   = 0,
  R_ERROR                = 1,
  R_NOT_FOUND            = 2,
  R_CAR_SET              = 3,
  R_PAYMENT_CANCEL_ERROR = 4,

  // SOAP
  R_SERVER_IS_UNAVAILABLE     = 1001,
  R_PROTOCOL_PROCESSING_ERROR = 1002,

  // ACL
  R_ACL_USER_NOT_AUTHENTICATED    = 10001,
  
  // License
  R_LICENSE_NOT_FOUND    = 11001,
  R_LICENSE_EXPIRED      = 11002,
  R_LICENSE_INVALID      = 11003

};

#endif // __RETURNS_H__