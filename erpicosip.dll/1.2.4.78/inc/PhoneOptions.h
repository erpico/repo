#ifndef __PHONEOPTIONS_H__
#define __PHONEOPTIONS_H__

#define PHONE_SIP_REGISTRY_PATH L"Software\\Erpico\\PhoneSip"

BOOL LogonUI(PHANDLE phToken);
BOOL IsUserInAdminGroup();
BOOL IsRunAsAdmin();
class PhoneOptions
{
public:
  static void errorMessageBox();
  static void setSaveStatus(bool hasErrorSave);
  static void setTempSettings(GUID micDevice, GUID playbackDevice, UINT ringDevice);
  static bool getMicDevice(GUID &deviceId);
  static LONG setMicDevice(GUID &deviceId);

  static bool getPlaybackDevice(GUID &deviceId);
  static LONG setPlaybackDevice(GUID &deviceId);

  static int getMicVolume();
  static void setMicVolume(int volume);

  static int getPlaybackVolume();
  static void setPlaybackVolume(int volume);

  static bool getRingDevice(UINT &deviceId);
  static LONG setRingDevice(UINT &deviceId);

private:
  static bool hasErrorSave_;
  static GUID micDevice_;
  static GUID playbackDevice_;
  static UINT ringDevice_;
  static LONG saveSettingGuid(const TCHAR *section, const TCHAR *option, const GUID &value);
  static bool getSettingGuid(const TCHAR *section, const TCHAR *option, GUID &value);

  static LONG saveSettingDWORD(const TCHAR *section, const TCHAR *option, const DWORD &value);
  static bool getSettingDWORD(const TCHAR *section, const TCHAR *option, DWORD &value);  

};
#endif