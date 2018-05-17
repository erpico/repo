#ifndef __SOUND_H__
#define __SOUND_H__
//#include <mmreg.h>
#include <mmsystem.h>
#include <initguid.h>
#include <dsound.h>
#include <dsconf.h>

BOOL GetInfoFromDSoundGUID( GUID i_sGUID, DWORD &dwWaveID, CStringA &Description, CStringA &Module, CStringA &Interface);
HRESULT DirectSoundPrivateCreate (OUT LPKSPROPERTYSET * ppKsPropertySet);

class Mixer
{
public:
  Mixer();
  ~Mixer();
  BOOL on();
  BOOL off();
  DWORD getControlValue();
  BOOL setControlValue(DWORD value);
};
#endif