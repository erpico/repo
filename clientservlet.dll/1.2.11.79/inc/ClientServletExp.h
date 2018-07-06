#pragma once

#ifdef CLIENTSERVLET_EXPORTS
#define CLIENTSERVLET_API __declspec(dllexport)
#else
#define CLIENTSERVLET_API __declspec(dllimport)
#endif