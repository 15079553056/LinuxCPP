#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <string>
#include <vector>

class CStringHelper
{
public:
    //字符串分割
    static void Split(const std::string& strSrc,std::vector<std::string>& vecDest,const char* delimiter);
    //根据 delimiter 指定的字符串，将字符串切割成两半
    static void Cut(const std::string& strSrc,std::vector<std::string>& vecDest,const char* delemiter);
    //字符串替换
    static std::string& Replace(std::string& strSrc,const std::string& strToReplaced,const std::string& strNew);
    //去除左侧字符
    static void TrimLeft(std::string& strSrc,char trimmed);
    //去除右侧字符
    static void TrimRight(std::string& strSrc,char trimmed);
    //去除左右两侧字符
    static void TrimLeftAndRight(std::string& str, char trimmed = ' ');
    //去除字符串中的字符串
    static void Trim(std::string& strSrc, const std::string& strMark);

private:
    //禁止构造函数
    CStringHelper()=delete;
    ~CStringHelper()=delete;
    //禁止拷贝构造函数
    CStringHelper(const CStringHelper& rhs)=delete;
    CStringHelper& operator=(const CStringHelper& rhs)=delete;
};

#endif
