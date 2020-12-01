#include "AsyncLog.h"
#include <iostream>
#include "../toollib/DirectoryHelper.h"
#include "../toollib/TimeHelper.h"


bool CAsyncLog::init(const char* pszLogFileName)
{
    //获取进程id
    char szPID[8]={0};
#ifdef WIN32
    snprintf(szPID, sizeof(szPID), "%05d", (int)::GetCurrentProcessId());
#else
    snprintf(szPID,sizeof("%05d"),(int)::getpid());
#endif

    m_strPID=szPID;
    //绑定执行写日志线程方法
    m_spWriteThread.reset(new std::thread(writeThreadProc));

    return true;
}


void CAsyncLog::uninit()
{

    //回收线程所占用的资源
    

}

/*
*
*/
void CAsyncLog::write(short nLevel,const char* pszFileName,const char* pszFuncName,int nLineNo,const char* pszLogMsg)
{

    std::string strLine="";
    
#pragma region 添加前缀
    switch (nLevel)
    {
    case LOG_LEVEL::LOG_LEVEL_TRACE:
        strLine="[trace]";
        break;
    case LOG_LEVEL::LOG_LEVEL_DEBUG:
        strLine="[debug]";
        break;
    case LOG_LEVEL::LOG_LEVEL_INFO:
        strLine="[info]";
        break;
    case LOG_LEVEL::LOG_LEVEL_WARN:
        strLine="[warn]";
        break;
    case LOG_LEVEL::LOG_LEVEL_ERROR:
        strLine="[error]";
        break;
    case LOG_LEVEL::LOG_LEVEL_SYSERROR:
        strLine="[syserror]";
        break;
    case LOG_LEVEL::LOG_LEVEL_FATAL:
        strLine="[fatal]";
        break;
    default:
        std::cout<<"in AsyncLog.cpp, CAsyncLog::write, the param nLevel is error";
        break;
    }
#pragma endregion

    //获取当前时间
    std::string strTime;
    CTimeHelper::getCurrentTime(strTime);

    char szFileName[512]={0};
    snprintf(szFileName,512,"[%s %s %s %d] %s",strTime.c_str(),pszFileName,pszFuncName,nLineNo,pszLogMsg);
    strLine+=szFileName;

    {
        //日志入队
        std::lock_guard<std::mutex> lock_guard(m_mutexWrite);
        m_listLinesToWrite.push_back(strLine);
        //触发事件信号
        m_cvWrite.notify_one();
    }
}


void CAsyncLog::writeThreadProc()
{
    while (true)
    {
        std::string strLine;

        {
            //括号内的std::unique_lock生命周期内，所管理的锁对象会一直保持上锁状态
            std::unique_lock<std::mutex> guard(m_mutexWrite);
            //阻塞住等待有触发才会执行下去，不然会一直阻塞在这一行代码
            m_cvWrite.wait(guard);
            //获取第一个元素
            strLine=m_listLinesToWrite.front();
            //获取后将第一个元素删除
            m_listLinesToWrite.pop_front();
        }

        //获取时间，localtime函数为非线程安全，所以使用下面两个方法
        time_t now=time(NULL);
        tm time;
#ifdef _WIN32
        localtime_s(&time,&now);  
#else
        localtime_r(&now,&time);
#endif

        //根据当前可执行程序的相对路径，年/月/日/小时，创建多级目录
        std::string strLogFilePath="";
        //年目录
        char szYear[10]={0};
#ifdef _WIN32
        sprintf(szYear,"%d\\",1900+time.tm_year);
#else
        sprintf(szYear,"%d/",1900+time.tm_year);
#endif
        strLogFilePath+=szYear;

        //月目录
        char szMonth[10]={0};
#ifdef _WIN32
        sprintf(szMonth,"%d\\",1+time.tm_mon);
#else
        sprintf(szMonth,"%d/",1+time.tm_mon);
#endif
        strLogFilePath+=szMonth;

        //日目录
        char szDay[10]={0};
#ifdef _WIN32
        printf(szDay,"%d\\",time.tm_mday);
#else 
        printf(szDay,"%d/",time.tm_mday);
#endif
        strLogFilePath+=szDay;

        //前缀目录
        char szPrefix[10]={0};
#ifdef _WIN32
        sprintf(szPrefix, "%s\\", strLine.substr(0, 1 + strLine.find_first_of(']', 0)).c_str());
#else 
        sprintf(szPrefix, "%s/", strLine.substr(0, 1 + strLine.find_first_of(']', 0)).c_str());
#endif

        //判断目录是否存在，不存在则创建
        if(!CDirectoryHelper::DirIsExist(strLogFilePath))
        {
            if(!CDirectoryHelper::DirCreate(strLogFilePath))
            {
                std::cout<<"in AsyncLog.cpp, AsyncLog::writeThreadProc -> CDirectoryHelper::DirCreate is fail"<<std::endl;
            }
        }


    }
}

