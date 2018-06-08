#pragma once

#include "Core.h"

class CORE_API CTts
{
public:
//  CTts();
//  ~CTts();

  struct sPrompt {
    unsigned long dwId;
    std::string   strText;
    time_t        lastModified;
    std::string   strUser;    
  };

  static int GetPrompts(const char* strFilter, std::list<sPrompt> & arrPrompts);
  static int GetPrompt(unsigned long dwId, sPrompt& sInfo);
  static unsigned long GetPrompt(const char* strText);
  static unsigned long SavePrompt(const char* strText);
  static int UpdateText(unsigned long dwId, const char* strNewText);
  static int DeletePrompt(unsigned long dwId);

};

