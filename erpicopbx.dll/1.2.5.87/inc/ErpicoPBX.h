#pragma once

#ifdef ERPICOPBX_EXPORTS
#define ERPICOPBX_API __declspec(dllexport)
#else
#define ERPICOPBX_API __declspec(dllimport)
#endif
