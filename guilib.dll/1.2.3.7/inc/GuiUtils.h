/*
 * GuiUtils.h
 * 
 *
 * Капралов А.
 * 17.9.2013 18:53
 */

#ifndef __GUIUTILS_H__
#define __GUIUTILS_H__

#include "GuiLib.h"

GUILIB_API HTREEITEM GetNextTreeItem(CTreeCtrl *treeCtrl, HTREEITEM hItem);
GUILIB_API void DeleteTreeItemData(CTreeCtrl *treeCtrl);

#endif // __GUIUTILS_H__