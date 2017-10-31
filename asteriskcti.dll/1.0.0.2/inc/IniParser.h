#pragma once
#include <map>
#include <string>

typedef std::map<std::string, std::string> MParameters;
typedef std::pair<std::string, std::string> PParameters;

class deprecated_CIniParser
{
public:
  static MParameters Parse(std::string filename, std::string sectionName );
  static std::string createTrimString( const std::string str );
};
