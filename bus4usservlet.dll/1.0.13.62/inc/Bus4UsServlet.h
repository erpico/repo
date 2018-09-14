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
    /* Авторизация */
    void AuthFunc(Json::Value &root, Json::Value &resul);
    /* Получить список текущих заказов */
    void GetOrders(Json::Value &root, Json::Value &result);
    /* Получить информацию о заказе */
	void GetOrder(Json::Value &root, Json::Value &result);
    /* Создание/редактирование заказа */
    void CreateOrder(Json::Value &root, Json::Value &result);
    /* Изменение состояния заказа */
    void ChangeState(Json::Value &root, Json::Value &result);
    /* Получение списка городов */
    void GetCities(Json::Value &root, Json::Value &result);
    /* Получение списка водителей */
	void GetExecutors(Json::Value &root, Json::Value &result);
    /* Получение списка клиентов */
	void GetClients(Json::Value &root, Json::Value &result);
    /* Проверка токена */
	bool CheckToken(const std::string &_strToken, Json::Value &root, Json::Value &result, DWORD &_dwUserId);
    /* Получение типов транспортных средств */
    void GetVehicleTypes(Json::Value &root, Json::Value &result);
    /* Создание/редактирование транспортных средств */
    void CreateVehicleType(Json::Value &root, Json::Value &result);
    /* Удаление типа транспортного средства */
    void DeleteVehicleType(Json::Value &root, Json::Value &result);
    /* Получение списка транспортных средств */
    void GetVehicles(Json::Value &root, Json::Value &result);
    /* Создание транспортного средства */
    void CreateVehicle(Json::Value &root, Json::Value &result);
    /* Сменить состояние водителя */
    void ChangeExecutorState(Json::Value &root, Json::Value &result);
    /* Удаление клиента */
    void DeleteClient(Json::Value &root, Json::Value &result);
    /* Создание/редактирование клиента */
    void CreateClient(Json::Value &root, Json::Value &result);
    /* Создание записи в services_citys */
    void CreateServiceCity(Json::Value &root, Json::Value &result);
    /* Редактирование записи в services_citys */
    void UpdateServiceCity(Json::Value &root, Json::Value &result);
    /* Удаление записи из services_citys */
    void DeleteServiceCity(Json::Value &root, Json::Value &result);
    /* Восстановление запписи в services_citys */
    void RestoreServiceCity(Json::Value &root, Json::Value &result);
    /* Выбор записи из services_citys */
    void SelectServiceCity(Json::Value &root, Json::Value &result);
    /* Выбор записей из services_citys */
    void CBus4UsServlet::SelectServiceCities(Json::Value &root, Json::Value &result);
    /* Привязать ТС к водителю */
    void AssignVehiclesToDriver(Json::Value &root, Json::Value &result);
    /* Получить привязанные к водителю транспортные средства */
    void GetAssignedVehicles(Json::Value &root, Json::Value &result);
    /* Создание/редактирование исполнителя */
    void CreateExecutor(Json::Value &root, Json::Value &result);
    /* Получение классов автомобиля */
    void GetCarClasses(Json::Value &root, Json::Value &result);
    /* Получить координаты ТС */
    void GetCarsCoords(Json::Value &root, Json::Value &result);
    /* Удалить транспортное средство */
    void DeleteVehicle(Json::Value &root, Json::Value &result);
    /* Получить ТС */
    void GetVehicle(Json::Value &root, Json::Value &result);
    /* Получить доп. опции ТС */
    void GetVehicleOptions(Json::Value &rot, Json::Value &result);
    /* Назначить автобус на заказ */
    void AssignBusToOrder(Json::Value &root, Json::Value &result);
    /* Назначить водителя на автобус */
    void AssignDriverToOrder(Json::Value &root, Json::Value &result);
    /* Получить справочник тарифов */
    void GetTariffs(Json::Value &root, Json::Value &result);
    /* Создать/редактировать тариф */
    void CreateTariff(Json::Value &root, Json::Value &result);
    /* Удалить справочник тарифов */
    void DeleteTariff(Json::Value &root, Json::Value &result);
    /* Получить группу тарифов */
    void GetTariffGroups(Json::Value &root, Json::Value &result);
    /* Создать/отредактировать группу тарифов */
    void CreateTariffGroup(Json::Value &root, Json::Value &result);
    /* Удалить тарифную группу */
    void DeleteTariffGroup(Json::Value &root, Json::Value &result);
    /* Получить классы автомобилей */
    void GetVehicleClasses(Json::Value &root, Json::Value &result);
    /* Удаление класса автомобиля */
    void DeleteVehicleClass(Json::Value &root, Json::Value &result);
    /* Создание класса транспортного средства */
    void CreateVehicleClass(Json::Value &root, Json::Value &result);
    /* Создание доп. опции */
    void CreateAdditionalOption(Json::Value &root, Json::Value &result);
    /* Получение доп. опций */
    void GetAdditionalOptions(Json::Value &root, Json::Value &result);
    /* Удаление доп. опции */
    void DeleteOption(Json::Value &root, Json::Value &result);
    /* Получение стоимости заказа */
    void GetOrderCost(Json::Value &root, Json::Value &result);
    /* Изменить статус платежа */
    void SetPayStatus(Json::Value &root, Json::Value &result);
    /* Получить типы поездки */
    void GetTripTypes(Json::Value &root, Json::Value &result);
    /* Принять или отклонить заказ подрядчиком */
    void ConfirmOrderByService(Json::Value &root, Json::Value &result);
    /* Назначение транспортного средства на заказ */
    void AssignVehicleToOrder(Json::Value &root, Json::Value &result);
    /* Получить типы верификации */
    void GetVerificationTypes(Json::Value &root, Json::Value &result);
    /* Установить информацию по заказу от подрядчика */
    void SetOrderInfoByService(Json::Value &root, Json::Value &result);
    /* Установить/снять флаг "Потерянные вещи" */
    void SetLostThings(Json::Value &root, Json::Value &result);
    /* Получить заказы для WebCRM подрядчика BT-ONE */
    void GetOrdersForService(Json::Value &root, Json::Value &result);
    /* Закрыть заказ подрядчиком */
    void SetFinishedByService(Json::Value &root, Json::Value &result);
    /* Подтерждение изменений по заказу подрядчиком */
    void ConfirmOrderChangesByService(Json::Value &root, Json::Value &result);
    /* Завершение заказа подрядчиком */
    void FinishOrderByService(Json::Value &root, Json::Value &result);
    /* Установка активности геозон */
    void SetGeozoneActive(Json::Value &root, Json::Value &result);
    /* Отчет по заказам */
    void GetOrdersReport(Json::Value &root, Json::Value &result);
    /* Отчет по водителям */
    void GetDriversReport(Json::Value &root, Json::Value &result);
    /* Отправка логина и пароля водителю по СМС */
    void SendLoginPasswordToDriver(Json::Value &root, Json::Value &result);
    /* Выставление признака "Счет перевозчику" */
    void SetServiceBill(Json::Value &root, Json::Value &result);
    /* Запрос звонка */
    void RequestCall(Json::Value &root, Json::Value &result);
    /* Запрос маршрута водителя по заказу */
    void GetDriverGPSLog(Json::Value &root, Json::Value &result);
    /* Блокирование подрядчика */
    void SetServiceState(Json::Value &root, Json::Value &result);
    /* Получение реквизитов перевозчика */
    void GetServiceDetails(Json::Value &root, Json::Value &result);
    /* Получение расстояния */
    void GetDistance(Json::Value &root, Json::Value &result);
    /* Сохранение отзыва по заказу */
    void SaveOrderReview(Json::Value &root, Json::Value &result);
    /* Получение отзывов по заказу или за период */
    void GetReviews(Json::Value &root, Json::Value &result);
    /* Выставление решение в пользу перевозчика или клиента */
    void SetReviewDecision(Json::Value &root, Json::Value &result);
    /* Пуш-уведомление водителю */
    void SendPushToDriver(Json::Value &root, Json::Value &result);
    /* СМС водителю */
    void SendSMSToDriver(Json::Value &root, Json::Value &result);

private:
    bool m_bInitialized;
    std::string strServerHost;
    std::string strLogin;
    std::string strPassword;
};