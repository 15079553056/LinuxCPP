#include "StringHelper.h"
#include <string.h>

/**
* @Description: 字符串分割
* @Param:
* @Return:
*/
void CStringHelper::Split(const std::string& str, std::vector<std::string>& v, const char* delimiter/* = "|"*/)
{
    if (delimiter == NULL || str.empty())
        return;

    std::string buf(str);
    size_t pos = std::string::npos;
    std::string substr;
    int delimiterlength = strlen(delimiter);
    while (true)
    {
        pos = buf.find(delimiter);
        if (pos != std::string::npos)
        {
            substr = buf.substr(0, pos);
            if (!substr.empty())
                v.push_back(substr);

            buf = buf.substr(pos + delimiterlength);

        }
        else
        {
            if (!buf.empty())
                v.push_back(buf);
            break;

        }

    }
}

/**
* @Description: 根据delimiter指定的字符串，将字符串切割成两半
* @Param:
* @Return:
*/
void CStringHelper::Cut(const std::string& str, std::vector<std::string>& v, const char* delimiter/* = "|"*/)
{
    if (delimiter == NULL || str.empty())
        return;

    std::string buf(str);
    size_t pos = buf.find(delimiter);
    if (pos == std::string::npos)
        return;

    std::string substr1 = buf.substr(0, pos);
    std::string substr2 = buf.substr(pos + 1);
    if (!substr1.empty())
        v.push_back(substr1);

    if (!substr2.empty())
        v.push_back(substr2);

}

/**
* @Description: 字符串替换
* @Param:
* @Return:
*/
std::string& CStringHelper::Replace(std::string& str, const std::string& toReplaced, const std::string& newStr)
{
    if (toReplaced.empty() || newStr.empty())
        return str;

    for (std::string::size_type pos = 0; pos != std::string::npos; pos += newStr.length())
    {
        pos = str.find(toReplaced, pos);
        if (pos != std::string::npos)
            str.replace(pos, toReplaced.length(), newStr);
        else
            break;

    }

    return str;

}

/**
* @Description: 去除左侧字符
* @Param:
* @Return:
*/
void CStringHelper::TrimLeft(std::string& str, char trimmed/* = ' '*/)
{
    std::string tmp = str;
    size_t length = tmp.length();
    for (size_t i = 0; i < length; ++i)
    {
        if (tmp[i] != trimmed)
        {
            str = tmp.substr(i);
            break;

        }

    }

}

/**
* @Description: 去除右侧字符
* @Param:
* @Return:
*/
void CStringHelper::TrimRight(std::string& str, char trimmed/* = ' '*/)
{
    std::string tmp = str;
    size_t length = tmp.length();
    for (int i = length - 1; i >= 0; --i)
    {
        if (tmp[i] != trimmed)
        {
            str = tmp.substr(0, i + 1);
            break;

        }

    }

}

/**
* @Description: 去除左右两侧字符
* @Param:
* @Return:
*/
void CStringHelper::TrimLeftAndRight(std::string& str, char trimmed/* = ' '*/)
{
    TrimLeft(str, trimmed);
    TrimRight(str, trimmed);

}

/**
* @Description: 去除字符串中的字符串
* @Param:
* @Return:
*/
void CStringHelper::Trim(std::string& strSrc, const std::string& strMark)
{
    size_t nSize = strMark.size();
    while (1)
    {
        size_t pos = strSrc.find(strMark);
        if (pos == std::string::npos)
        {
            return;

        }

        strSrc.erase(pos, nSize);
    }
}
