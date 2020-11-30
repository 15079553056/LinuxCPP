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
bool CAsyncLog::write(short nLevel,const char* pszFileName,const char* pszFuncName,int nLineNo,const char* pszLogMsg)
{

    std::string strLine;

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

        //根据当前可执行程序的相对路径，年/月/日/小时，创建多级目录
        
    }
}

