/*
 * SipController.h
 * 
 * Kapralov A.
 * 16.04.2014 21:08
 */

#ifndef __SIPCONTROLLER_H__
#define __SIPCONTROLLER_H__

#include "ErpicoSIP.h"

#include <pjsua2.hpp>

using namespace pj;

class SipAccount;

class ERPICOSIP_API SipCall : public Call
{
public:
  SipCall(Account &acc, HWND hWnd, int call_id = PJSUA_INVALID_ID);

  virtual void onCallState(OnCallStateParam &prm);
  virtual void onCallMediaState(OnCallMediaStateParam & prm);

  void setIncoming(bool incoming);
  bool isIncoming();
  std::string getNumber();
  void setNumber(std::string number);
private:
  SipAccount *account_;
  bool incoming_;
  HWND hWnd_;
  std::string number_;  
};

enum AudioDeviceType { CAPTURE_DEVICE, PLAYBACK_DEVICE };

class ERPICOSIP_API SipController : public Account {
public:
  SipController();
  virtual ~SipController();

  void createEndPoint();
  void destroyEndPoint();
  void initialize(int bindPort = 5068);

  void setAudioDevice(GUID, AudioDeviceType type);
  void setAudioDevice(int idx, AudioDeviceType type);
  void setAudioVolume(int volume, AudioDeviceType type);
  int getAudioPeakMeterValue(AudioDeviceType type);

  void setMessageHandler(HWND hWnd);

public:
  void setAccountProperties(const char *id, const char *registrar, const char *realm, 
    const char *user, const char *password);

private:
  void setAccountInfo(AccountConfig acc_cfg);

public:
  void call(const string number);
  void hangUp();  
  void answer();
  void sendDtmf(string digits);
  virtual void onRegStarted(OnRegStartedParam & prm);
  virtual void onRegState(OnRegStateParam &prm);  
  virtual void onIncomingCall(OnIncomingCallParam &iprm);
  
  SipCall* getCurrentCall();
private:
  static Endpoint* ep_;
  int currentCallId_;
  HWND hWnd_;  
  std::string strDomain;
};
#endif // __SIPCONTROLLER_H__
