#include "configReader.h"
#include <fstream>
#include <sstream>

std::map<std::string, std::string> ConfigReader::m_configValues;

bool ConfigReader::read(const std::string& fileName) {
   std::ifstream file(fileName);
   if (!file) {
      return false;
   }

   std::string line;
   while (std::getline(file, line)) {
      // Skip comments
      if (line[0] == '#') {
			continue;
		}
      std::istringstream iss(line);
      std::string key, value;
      if (std::getline(iss, key, '=') && std::getline(iss, value)) {
         m_configValues[key] = value;
      }
   }

   return true;
}

std::string ConfigReader::get(const std::string& key) {
   auto it = m_configValues.find(key);
   if (it != m_configValues.end()) {
      return it->second;
   }

   return "";
}