#ifndef __RECVPROCTHREAD_H
#define __RECVPROCTHREAD_H

#include "ErpicoCTI/WCTI_Def.h"

#include <windows.h>

typedef void (*CRECV_PROC)( LPVOID );

/*namespace com_cisco
{
  */
  class CRecvProcThread
  {
  public:
    CRecvProcThread(LPVOID);
    ~CRecvProcThread(void);
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

#endif // __RECVPROCTHREAD_H