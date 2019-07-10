#ifndef __ERPICOCHATEXP_H__
#define __ERPICOCHATEXP_H__

#include "acllib/AbstractAclApp.h"

#ifdef CHAT_EXPORT
#define CHAT_API __declspec(dllexport)
#else
#define CHAT_API __declspec(dllimport)
#endif

/* Запустить чат */
CHAT_API void RunErpicoChat(AbstractAclApp *app);

#endif // __ERPICOCHATEXP_H__