#pragma once

#include <afxwin.h>
#include "../ClientServlet/inc/ClientServlet.h"
#include "HttpLib/HttpServlet.h"
#include "Core/json/json.h"

const int const_iStep = 1000;

class CBus4UsServlet : public CClientServlet
{
public:
    CBus4UsServlet(){};
    virtual~ CBus4UsServlet(){};
    
    virtual int Init();
    virtual void ProcessRequest(CHttpRequest &_cRequest, CHttpResponse &_cResponse, const CHttpServer *pServer = NULL);
    bool IsInitialized();
    /* ����������� */
    void AuthFunc(Json::Value &root, Json::Value &resul);
    /* �������� ������ ������� ������� */
    void GetOrders(Json::Value &root, Json::Value &result);
    /* �������� ���������� � ������ */
	void GetOrder(Json::Value &root, Json::Value &result);
    /* ��������/�������������� ������ */
    void CreateOrder(Json::Value &root, Json::Value &result);
    /* ��������� ��������� ������ */
    void ChangeState(Json::Value &root, Json::Value &result);
    /* ��������� ������ ������� */
    void GetCities(Json::Value &root, Json::Value &result);
    /* ��������� ������ ��������� */
	void GetExecutors(Json::Value &root, Json::Value &result);
    /* ��������� ������ �������� */
	void GetClients(Json::Value &root, Json::Value &result);
    /* �������� ������ */
	bool CheckToken(const std::string &_strToken, Json::Value &root, Json::Value &result, DWORD &_dwUserId);
    /* ��������� ����� ������������ ������� */
    void GetVehicleTypes(Json::Value &root, Json::Value &result);
    /* ��������/�������������� ������������ ������� */
    void CreateVehicleType(Json::Value &root, Json::Value &result);
    /* �������� ���� ������������� �������� */
    void DeleteVehicleType(Json::Value &root, Json::Value &result);
    /* ��������� ������ ������������ ������� */
    void GetVehicles(Json::Value &root, Json::Value &result);
    /* �������� ������������� �������� */
    void CreateVehicle(Json::Value &root, Json::Value &result);
    /* ������� ��������� �������� */
    void ChangeExecutorState(Json::Value &root, Json::Value &result);
    /* �������� ������� */
    void DeleteClient(Json::Value &root, Json::Value &result);
    /* ��������/�������������� ������� */
    void CreateClient(Json::Value &root, Json::Value &result);
    /* �������� ������ � services_citys */
    void CreateServiceCity(Json::Value &root, Json::Value &result);
    /* �������������� ������ � services_citys */
    void UpdateServiceCity(Json::Value &root, Json::Value &result);
    /* �������� ������ �� services_citys */
    void DeleteServiceCity(Json::Value &root, Json::Value &result);
    /* �������������� ������� � services_citys */
    void RestoreServiceCity(Json::Value &root, Json::Value &result);
    /* ����� ������ �� services_citys */
    void SelectServiceCity(Json::Value &root, Json::Value &result);
    /* ����� ������� �� services_citys */
    void CBus4UsServlet::SelectServiceCities(Json::Value &root, Json::Value &result);
    /* ��������� �� � �������� */
    void AssignVehiclesToDriver(Json::Value &root, Json::Value &result);
    /* �������� ����������� � �������� ������������ �������� */
    void GetAssignedVehicles(Json::Value &root, Json::Value &result);
    /* ��������/�������������� ����������� */
    void CreateExecutor(Json::Value &root, Json::Value &result);
    /* ��������� ������� ���������� */
    void GetCarClasses(Json::Value &root, Json::Value &result);
    /* �������� ���������� �� */
    void GetCarsCoords(Json::Value &root, Json::Value &result);
    /* ������� ������������ �������� */
    void DeleteVehicle(Json::Value &root, Json::Value &result);
    /* �������� �� */
    void GetVehicle(Json::Value &root, Json::Value &result);
    /* �������� ���. ����� �� */
    void GetVehicleOptions(Json::Value &rot, Json::Value &result);
    /* ��������� ������� �� ����� */
    void AssignBusToOrder(Json::Value &root, Json::Value &result);
    /* ��������� �������� �� ������� */
    void AssignDriverToOrder(Json::Value &root, Json::Value &result);
    /* �������� ���������� ������� */
    void GetTariffs(Json::Value &root, Json::Value &result);
    /* �������/������������� ����� */
    void CreateTariff(Json::Value &root, Json::Value &result);
    /* ������� ���������� ������� */
    void DeleteTariff(Json::Value &root, Json::Value &result);
    /* �������� ������ ������� */
    void GetTariffGroups(Json::Value &root, Json::Value &result);
    /* �������/��������������� ������ ������� */
    void CreateTariffGroup(Json::Value &root, Json::Value &result);
    /* ������� �������� ������ */
    void DeleteTariffGroup(Json::Value &root, Json::Value &result);
    /* �������� ������ ����������� */
    void GetVehicleClasses(Json::Value &root, Json::Value &result);
    /* �������� ������ ���������� */
    void DeleteVehicleClass(Json::Value &root, Json::Value &result);
    /* �������� ������ ������������� �������� */
    void CreateVehicleClass(Json::Value &root, Json::Value &result);
    /* �������� ���. ����� */
    void CreateAdditionalOption(Json::Value &root, Json::Value &result);
    /* ��������� ���. ����� */
    void GetAdditionalOptions(Json::Value &root, Json::Value &result);
    /* �������� ���. ����� */
    void DeleteOption(Json::Value &root, Json::Value &result);
    /* ��������� ��������� ������ */
    void GetOrderCost(Json::Value &root, Json::Value &result);
    /* �������� ������ ������� */
    void SetPayStatus(Json::Value &root, Json::Value &result);
    /* �������� ���� ������� */
    void GetTripTypes(Json::Value &root, Json::Value &result);
    /* ������� ��� ��������� ����� ����������� */
    void ConfirmOrderByService(Json::Value &root, Json::Value &result);
    /* ���������� ������������� �������� �� ����� */
    void AssignVehicleToOrder(Json::Value &root, Json::Value &result);
    /* �������� ���� ����������� */
    void GetVerificationTypes(Json::Value &root, Json::Value &result);
    /* ���������� ���������� �� ������ �� ���������� */
    void SetOrderInfoByService(Json::Value &root, Json::Value &result);
    /* ����������/����� ���� "���������� ����" */
    void SetLostThings(Json::Value &root, Json::Value &result);
    /* �������� ������ ��� WebCRM ���������� BT-ONE */
    void GetOrdersForService(Json::Value &root, Json::Value &result);
    /* ������� ����� ����������� */
    void SetFinishedByService(Json::Value &root, Json::Value &result);
    /* ������������ ��������� �� ������ ����������� */
    void ConfirmOrderChangesByService(Json::Value &root, Json::Value &result);
    /* ���������� ������ ����������� */
    void FinishOrderByService(Json::Value &root, Json::Value &result);
    /* ��������� ���������� ������ */
    void SetGeozoneActive(Json::Value &root, Json::Value &result);
    /* ����� �� ������� */
    void GetOrdersReport(Json::Value &root, Json::Value &result);
    /* ����� �� ��������� */
    void GetDriversReport(Json::Value &root, Json::Value &result);
    /* �������� ������ � ������ �������� �� ��� */
    void SendLoginPasswordToDriver(Json::Value &root, Json::Value &result);
    /* ����������� �������� "���� �����������" */
    void CBus4UsServlet::SetServiceBill(Json::Value &root, Json::Value &result);
    /* ������ ������ */
    void CBus4UsServlet::RequestCall(Json::Value &root, Json::Value &result);
    /* ������ �������� �������� �� ������ */
    void GetDriverGPSLog(Json::Value &root, Json::Value &result);
    /* ������������ ���������� */
    void SetServiceBlocked(Json::Value &root, Json::Value &result);
    /* ��������� ���������� ����������� */
    void GetServiceDetails(Json::Value &root, Json::Value &result);
    /* ��������� ���������� */
    void GetDistance(Json::Value &root, Json::Value &result);

private:
    bool m_bInitialized;
    std::string strServerHost;
    std::string strLogin;
    std::string strPassword;
};