/*
 * GuiLib.h
 * 
 *
 * Капралов А.
 * 26.2.2013 12:55
 */

#ifndef __GUILIB_H__
#define __GUILIB_H__

#ifdef GUILIB_EXPORTS
#define GUILIB_API __declspec(dllexport)
#else
#define GUILIB_API __declspec(dllimport)
#endif

#endif // __GUILIB_H__
