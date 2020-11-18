#include "AsyncLog.h"

bool CAsyncLog::init(const char* pszLogFileName)
{
    //获取进程id
    char szPID[8]={0};
#ifdef WIN32
    snprintf(szPID, sizeof(szPID), "%05d", (int)::GetCurrentProcessId());
#else
    snprintf(szPID,sizeof("%05d"),(int)::getpid());
#endif

}


void CAsyncLog::uninit()
{

    //回收线程所占用的资源
    

}




