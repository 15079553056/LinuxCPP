#ifndef CONFIGFILEREADER_H
#define CONFIGFILEREADER_H

#include <map>
#include <string>

class CConfigFileReader
{
public:
    //
    CConfigFileReader(const char* pszFilePath);
    //
    ~CConfigFileReader();
    
    //根据名称获取值
    const char* getConfValByName(const char* pszName) const; 
    //
    bool setConfVal();
};

#endif