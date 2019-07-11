/*
 * MFCUtils.h
 * 
 * Kapralov A.
 * 5.12.2013 17:27
 */
#ifndef __MFCUTILS_H__
#define __MFCUTILS_H__

#include "GuiLib.h"

class GUILIB_API MFCUtils {
public:
  // Delete all of the children of hItem. 
  static void DeleteAllChildItems(CTreeCtrl &treeCtrl, HTREEITEM hItem);
};

#endif // __MFCUTILS_H__

