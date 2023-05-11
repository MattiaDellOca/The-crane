#pragma once

#include <string>
#include <map>

class ConfigReader {
public:
   static bool read(const std::string& fileName);

   static std::string get(const std::string& key);
private:
   static std::map<std::string, std::string> m_configValues;
};