#include "TimeHelper.h"

#include <chrono>
//#include <time.h>

std::string& CTimeHelper::getCurrentTime(std::string& strTime)
{
    std::chrono::system_clock::time_point now=std::chrono::system_clock::now();
    //转换为std::time_t格式
    std::time_t nowTime=std::chrono::system_clock::to_time_t(now);
    struct tm* ptm=localtime(&nowTime);
    char date[60]={0};
    sprintf(date,"%d/%02d/%02d %02d:%02d:%02d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
    strTime=date;
    return strTime;
}
