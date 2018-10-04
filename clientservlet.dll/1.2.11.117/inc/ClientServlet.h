#ifndef __CLIENTSERVLET_H__
#define __CLIENTSERVLET_H__

#include "ClientServletExp.h"

#include "HttpLib/HttpServlet.h"

#include "HttpLib/HttpServer.h"

#include "Core/json/json.h"

#include "CRMCore/Zakaz.h"

#include "CRMCore/ClientHelper.h"

class CLIENTSERVLET_API CClientServlet : public CHttpServlet
{
private:
  bool m_bInitialized;
  ClientHelper m_clientHelper;

public:
  CClientServlet();
  virtual ~CClientServlet();

public:
  bool IsInitialized();
  virtual int Init();
  static int GetPayType(const char* strPayType);
  static string GetPayType(int iPayType);
  static int GetOrderType(const char* strOrderType);
  string GetOrderType(int iOrderType);
  ClientHelper* GetHelper();
  static void getAdditionalOptionsFunc(Json::Value &root, Json::Value &result);

public:
  virtual void ProcessRequest(CHttpRequest &_cRequest, CHttpResponse &_cResponse, const CHttpServer *pServer = NULL);
  static void ParseAddress( CZakaz::ADDRESS_INFO &addressInfo, Json::Value &address );
  void GetProcessOrderFunc(Json::Value &root, Json::Value &result)
  {
    processOrder(root, result);
  };
  bool CheckToken(const std::string &_strToken, DWORD &_dwClientId, const std::string &_strError, Json::Value &_result);
  void StopAllThreads();
    
private:
  void processRequestCode(Json::Value &root, Json::Value &result);
  void processVerifyCode(Json::Value &root, Json::Value &result);
  void processAuthenticate(Json::Value &root, Json::Value &result);
  void processState(Json::Value &root, Json::Value &result);
  void processUpdateClient(Json::Value &root, Json::Value &result);
  void UpdateClient(const char *token, const Json::Value &root, Json::Value &result);
  void appendClient(const char *token, Json::Value &result );
  void appendClient( DWORD clientId, Json::Value &result );
  void appendOrders(DWORD clientId, CZakaz::eState * states, Json::Value &node);
  void appendOrder(const CZakaz::ZAKAZ_INFO &orderInfo, Json::Value &jsonOrders);
  void toJson(CZakaz::ADDRESS_INFO &addressInfo, Json::Value &jsonAddress);
  void processOrder(Json::Value &root, Json::Value &result);
  void processRequestCall(Json::Value &root, Json::Value &result);
  void processCancelOrder(Json::Value &root, Json::Value &result);
  void processGetOrdersArchive(Json::Value &root, Json::Value &result);
  void clientPhoneOrderAction(Json::Value &root, Json::Value &result);
  void searchOrdersByPhone(Json::Value &root, Json::Value &result);
  void rechargeAccount(Json::Value &root, Json::Value &result);
  void calcSumDistance(Json::Value &root, Json::Value &result);
  void getCarsInfo(Json::Value &root, Json::Value &result);
  void getTaxiMeterInfo(Json::Value &root, Json::Value &result);
  void getStreetsMethod(Json::Value &root, Json::Value &result);
  void getCitiesMethod(Json::Value &root, Json::Value &result);
  void getCarClassesMethod(Json::Value &root, Json::Value &result);
  void getAdditionalOptions(Json::Value &root, Json::Value &result);  
  void processGeocode(Json::Value &root, Json::Value &result);  
  void processGetCountriesAndRegions(Json::Value &root, Json::Value &result);
};

#endif // __CLIENTSERVLET_H__

