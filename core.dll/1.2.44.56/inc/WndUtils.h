#pragma once

#define WarningMessageBox(szMessage) MessageBox(szMessage, "Ошибка", MB_OK | MB_ICONWARNING)
#define DBWarningMessageBox(szMessage) MessageBox(szMessage, "Ошибка Базы Данных", MB_OK | MB_ICONWARNING)

#define ErrorMessageBox(szMessage) MessageBox(szMessage, "Критическая ошибка", MB_OK | MB_ICONERROR)

#define DelConfirmMessageBox(szMessage) MessageBox(szMessage, "Подтверждение удаления", MB_YESNO | MB_ICONWARNING)
