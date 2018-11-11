/************************************************************************
 *  created:    20.08.2008  12:12
 *  filename:   ServConf.h
 *  author:     Mirzoyan A.
 *
 *  purpose:    configuration header file for the HttpServer
 *  version:    1.0
 ************************************************************************/

#ifndef __ServConf_h__
#define __ServConf_h__

#define _SERV_CONF_DECLSPEC __declspec( dllexport )

class _SERV_CONF_DECLSPEC CServConf
{
private:
  static char str_conf_file[256];
  static char m_strAllowedIPs[4096];
  static int Port;
  static int MaxConnections;
public:
  // �������������
  static void Init(char *strFName);
  // ����� ����������� IP
  static char* GetStrAllowedIPs();

  // �������� ������������� �������� ��������. ���� ����� ����������� - �������
  static  int GetIntServletParam(int iServlet, const char *strParam, int iDefault = 0);
  // �������� ��������� �������� ��������. ���� ����� ����������� - �������
  static void GetStrServletParam(int iServlet, const char *strParam, 
                                 char *strResult, const char *strDefault = "");

  // �������� ���� �������
  static  int GetHttpServPort();
  // �������� max_connections
  static  int GetHttpServMaxConnections();
  // �������� ����� ���������
  static  int GetServletCount();

  // �������� ��� ��������
  static void GetStrServletName(int iServlet, char *strResult);
  // �������� ���� ��������
  static void GetStrServletFile(int iServlet, char *strResult);
};

#endif // __ServConf_h__
