#ifndef __RECVTHREAD_H
#define __RECVTHREAD_H

#include "ErpicoCTI/WCTI_Def.h"

#include <windows.h>

typedef void (*CRECV_PROC)( LPVOID );

/*namespace com_cisco
{
  */
  class CRecvThread
  {
  public:
    CRecvThread(LPVOID);
    ~CRecvThread(void);
    void start();
    HANDLE getHandle(){ return hThread;};
    DWORD getThreadId(){return threadId;};
  private:
    HANDLE hThread;
    DWORD threadId;
    LPVOID m_param;
    CRECV_PROC m_proc;

    static DWORD WINAPI threadProc( LPVOID );
  };
//}

#endif // __RECVTHREAD_H