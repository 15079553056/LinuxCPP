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
    char* getConfVal(const char* pszName); 
    //设置值
    bool setConfVal(const char* pszName,const char* pszVal);

private:
    //加载文件
    void loadFile(const char* pszFilePath);
    //写入配置文件
    int writeFile();
    //去除空格和换行符
    char* trimSpace(char* pszName);
    

private:
    std::map<std::string,std::string>   m_mapConfig;            //配置文件字典集合                
    std::string                         m_strConfigPath;        //配置文件路径
    bool                                m_bIsLoadOK;            //配置文件是否成功加载
};

#endif