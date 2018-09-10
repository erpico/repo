/*
 * AclLib.h
 * 
 *
 * Капралов А.
 * 11.3.2013 16:05
 */
#ifndef __ACLLIB_H__
#define __ACLLIB_H__

#ifdef ACLLIB_EXPORTS
#define ACLLIB_API __declspec(dllexport)
#else
#define ACLLIB_API __declspec(dllimport)
#endif

#endif // __ACLLIB_H__

