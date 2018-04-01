/************************************************************************
*  created:    27.6.2007  11:06
*  filename:   XMLNode.h
*  author:     Kapralov A.
*
*  purpose:    CXMLNode - класс узел XML-документа.
*  version:    1.0
************************************************************************/

#ifndef __XMLNODE_H__
#define __XMLNODE_H__

#include "Core.h"

#include <map>
#include <list>
#include "afxmt.h"

#pragma warning(disable: 4192) // warning C4192: automatically excluding 'ISequentialStream' while importing type library 'MSXML6.dll'

#import "MSXML6.dll" named_guids 

//using namespace MSXML2;

// Узел XML-документа.
// Author: Kapralov A.
class
    CORE_API CXMLNode {
public:
  static CCriticalSection g_CritCoOperation;
  // Конструктор.
  CXMLNode();
  // Конструктор.
  // _pNode - узел XML-документа.
  CXMLNode(MSXML2::IXMLDOMNodePtr _pNode);
  CXMLNode& operator=(const CXMLNode &src);

  // Деструктор.
  ~CXMLNode();

  //Проверка на пустой узел
  bool IsOk() {
    return (m_pNode != NULL);
  }

  // Преобразовывает узел к его строковому представлению.
  // _string - результирующая строка.
  void ToString(CString &_string);

  // Получает имя узла.
  // _name - результирующая строка.
  bool CXMLNode::GetName(CString &_name);

  // Имеет ли данный элемент дочерний узел с соответствующим именем.
  // _name - имя дочернего узла.
  // Возвращает: true - если дочерний узел присутствует, false - иначе.
  bool HasChild(const char *_name);

  // Получает дочерний узел с заданным именем.
  // _szName - имя узла.
  // Возвращает: дочерний узел с заданным именем.
  // Пустой узел, если дочернего узла с таким именем 
  // не существует.
  CXMLNode GetChildNode(const char *_szName);

  // Прикрепляет дочерний узел с заданным именем.
  // Возвращает: результирующий узел.
  // Пустой узел, если произошла ошибка.
  CXMLNode AppendChild(const char *_szName);
  // Прикрепляет дочерний узел с заданным именем и значением.
  // _name - имя узла.
  // _value - значение.
  bool AppendChild(const char *_name, const char *_value);
  // Прикрепляет дочерний узел с заданным именем и значением.
  // _name - имя узла.
  // _value - значение.
  bool AppendChild(const char *_name, long _value);
  // Прикрепляет дочерний узел с заданным именем и значением.
  // _name - имя узла.
  // _value - значение.
  bool AppendChild(const char *_name, unsigned long _value);
  // Прикрепляет дочерний узел с заданным именем и значением.
  // _name - имя узла.
  // _value - значение.
  bool AppendChild(const char *_name, int _value);
  // Прикрепляет дочерний узел с заданным именем и значением.
  // _name - имя узла.
  // _value - значение.
  bool AppendChild(const char *_name, long long _value);
  // Прикрепляет дочерний узел с заданным именем и значением.
  // _name - имя узла.
  // _value - значение.
  // _format - формат записи (такой же как и у printf, только без 
  // символа типа, например, "1.2").
  bool AppendChild(const char *_name, float _value, const char *_format = NULL);
  // Прикрепляет дочерний узел с заданным именем и значением.
  // _name - имя узла.
  // _value - значение.
  // _format - формат записи (такой же как и у printf, только без 
  // символа типа, например, "1.2").
  bool AppendChild(const char *_name, double _value, const char *_format = NULL);
  // Прикрепляет дочерний узел.
  // _childNode - дочерний узел.
  bool AppendChild(CXMLNode &_childNode);

  // Получает текстовое содержание узла.
  // _buffer - результирующая строка.
  // Возвращает: false, если узел не имеет содержания или 
  // это содердание не является типом текст.
  bool GetTextContent(CString &_buffer);
  // Получает содержание узла в виде типа long.
  // Возвращает: false, если узел не имеет содержания или 
  // это содердание не является типом long.
  bool GetLongContent(long &value);
  // Получает содержание узла в виде типа unsigned long.
  // Возвращает: false, если узел не имеет содержания или 
  // это содердание не является типом unsigned long.
  bool GetUnsignedLongContent(unsigned long &value);
  // Получает содержание узла в виде типа int.
  // Возвращает: false, если узел не имеет содержания или 
  // это содердание не является типом int.
  bool GetIntContent(int &value);
  // Получает содержание узла в виде типа int64.
  // Возвращает: false, если узел не имеет содержания или 
  // это содердание не является типом int64.
  bool GetInt64Content(long long &value);
  // Получает содержание узла в виде типа float.
  // Возвращает: false, если узел не имеет содержания или 
  // это содердание не является типом float.
  bool GetFloatContent(float &value);
  // Получает содержание узла в виде типа double.
  // Возвращает: false, если узел не имеет содержания или 
  // это содердание не является типом double.
  bool GetDoubleContent(double &value);

  // Устанавливает содержание узла.
  // _value - значение.
  bool SetContent(const char *_value);
  // Устанавливает содержание узла.
  // _value - значение.
  bool SetContent(long _value);
  // Устанавливает содержание узла.
  // _value - значение.
  bool SetContent(int _value);
  // Устанавливает содержание узла.
  // _value - значение.
  bool SetContent(long long _value);
  // Устанавливает содержание узла.
  // _value - значение.
  // _format - формат записи (такой же как и у printf, только без 
  // символа типа, например, "1.2").
  bool SetContent(float _value, const char *_format = NULL);

  // Имеет ли данный элемент атрибут с соответствующим именем.
  // _name - имя атрибута.
  // Возвращает: true - если атрибут присутствует, false - иначе.
  bool HasAttribute(const char *_name);

  // Получает текстовый атрибут узла с заданным именем.
  // _name - имя атрибута.
  // _buffer - результирующая строка.
  bool GetDoubleAttribute(const char *_name, double &value);
  // Получает текстовый атрибут узла с заданным именем.
  // _name - имя атрибута.
  // _buffer - результирующая строка.
  bool GetFloatAttribute(const char *_name, float &value);
  // Получает текстовый атрибут узла с заданным именем.
  // _name - имя атрибута.
  // value - возвращаемое значение атрибута узла.
  bool GetTextAttribute(const char *_name, CString &_buffer);
  // Получает атрибут узла с заданным именем типа int.
  // _name - имя атрибута.
  // value - возвращаемое значение атрибута узла.
  bool GetIntAttribute(const char *_name, int &value);
  // Получает атрибут узла с заданным именем типа long.
  // _name - имя атрибута.
  // value - возвращаемое значение атрибута узла.
  bool GetLongAttribute(const char *_name, long &value);
  // Получает атрибут узла с заданным именем типа int64.
  // _name - имя атрибута.
  // value - возвращаемое значение атрибута узла.
  bool GetInt64Attribute(const char *_name, long long &value);
  // Получает атрибут узла с заданным именем типа unsigned long.
  // _name - имя атрибута.
  // value - возвращаемое значение атрибута узла.
  bool GetUnsignedLongAttribute(const char *_name, unsigned long &value);

  // Устанавливает значение атрибута с заданным именем.
  // _name - имя атрибута.
  // _value - новое значение атрибута.
  bool SetAttribute(const char *_name, const char *_value);
  // Устанавливает значение атрибута с заданным именем.
  // _name - имя атрибута.
  // _value - новое значение атрибута.
  bool SetAttribute(const char *_name, double _value);
  // Устанавливает значение атрибута с заданным именем.
  // _name - имя атрибута.
  // _value - новое значение атрибута.
  bool SetAttribute(const char *_name, int _value);
  // Устанавливает значение атрибута с заданным именем.
  // _name - имя атрибута.
  // _value - новое значение атрибута.
  bool SetAttribute(const char *_name, long long _value);
  // Устанавливает значение атрибута с заданным именем.
  // _name - имя атрибута.
  // _value - новое значение атрибута.
  bool SetAttribute(const char *_name, long _value);
  // Устанавливает значение атрибута с заданным именем.
  // _name - имя атрибута.
  // _value - новое значение атрибута.
  bool SetAttribute(const char *_name, unsigned long _value);

  // Получает карту дочерних узлов. В карте ключом является имя узла, 
  // а значением сам узел.
  // _nodeMap - результирующая карта.
  bool GetChildsMap(std::map<CString, CXMLNode> &_nodeMap);
  // Получает список дочерних узлов. 
  // _nodeList - результирующий список.
  bool GetChildsList(std::list<CXMLNode> &_nodeList);

protected:

  // Возвращает оригинальный узел.
  MSXML2::IXMLDOMNodePtr GetDOMNode();
  // Устанавливает оригинальный узел документа.
  void SetDOMNode(MSXML2::IXMLDOMNodePtr _pNode);

private:
  friend class CXMLDocument;
  //friend class std::map;

  // Оригинальный указатель на узел XML-документа.
  MSXML2::IXMLDOMNodePtr m_pNode;

};


#endif // __XMLNODE_H__

