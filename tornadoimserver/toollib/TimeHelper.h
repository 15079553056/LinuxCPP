#ifndef TIMEHELPER_H
#define TIMEHELPER_H

#include <string>
/*
* 时间帮助类
* 使用C++ 11 的chrono库
* 
*/
class CTimeHelper
{

public:
    //获取当前时间，字符串类型
    static std::string& getCurrentTime(std::string& strTime);
    //获取当前时间戳，秒级别

    //获取当前时间戳，毫秒级别

private:
    //禁止构造函数
    CTimeHelper()=delete;
    ~CTimeHelper()=delete;
    //禁止拷贝构造函数
    CTimeHelper(const CTimeHelper& rhs)=delete;
    CTimeHelper& operator=(const CTimeHelper& rhs)=delete;

};

#endif