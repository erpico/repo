/************************************************************************
 *  created:    29.2.2008  19:10
 *  filename:   DebugNew.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __DEBUGNEW_H__
#define __DEBUGNEW_H__

#include "Core.h"

#ifdef DEBUG_MEMORY_LEAKS

#include <malloc.h>

CORE_API void AddTrack(void *_p, size_t _size, const char *_file, int _line);
CORE_API void RemoveTrack(void *_p);
CORE_API void DumpUnfreed();

inline void * __cdecl operator new(size_t _size, const char *_file, int _line) {
  void *ptr = (void *)malloc(_size);
  AddTrack(ptr, _size, _file, _line);
  return ptr;
}

inline void * __cdecl operator new[](size_t _size, const char *_file, int _line) {
  void *ptr = (void *)malloc(_size);
  AddTrack(ptr, _size, _file, _line);
  return ptr;
}

inline void * __cdecl operator new(size_t _size) {
  void *ptr = (void *)malloc(_size);
  return ptr;
}

inline void  __cdecl operator delete(void *_p) {
  RemoveTrack(_p);	
  free(_p);
}

inline void  __cdecl operator delete[](void *_p) {
  RemoveTrack(_p);	
  free(_p);
}

inline void __cdecl operator delete(void *_p, const char *_file, int _line) {
  RemoveTrack(_p);
  free(_p);
}

#ifdef DEBUG_NEW
#undef DEBUG_NEW
#endif // DEBUG_NEW
#define new DEBUG_NEW
#define DEBUG_NEW new(__FILE__, __LINE__)

#endif // DEBUG_MEMORY_LEAKS

#endif // __DEBUGNEW_H__