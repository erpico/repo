#pragma once

#define WarningMessageBox(szMessage) MessageBox(szMessage, "������", MB_OK | MB_ICONWARNING)
#define DBWarningMessageBox(szMessage) MessageBox(szMessage, "������ ���� ������", MB_OK | MB_ICONWARNING)

#define ErrorMessageBox(szMessage) MessageBox(szMessage, "����������� ������", MB_OK | MB_ICONERROR)

#define DelConfirmMessageBox(szMessage) MessageBox(szMessage, "������������� ��������", MB_YESNO | MB_ICONWARNING)
