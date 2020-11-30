#ifndef ASYNCLOG_H
#define ASYNCLOG_H

#include <stdio.h>
#include <list>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

//思路: 新开辟一个线程进行日志写入
//      应该设计为生产消费者模式，有一个队列存储需要写入的日志内容。
//      应该使用事件模型，每次写入线程函数进行阻塞，直到触发事件才进行下去。每触发一次事件，执行一次写入。

//日志等级
enum LOG_LEVEL
{
    LOG_LEVEL_TRACE,            //    TRACE 级，方法执行记录
    LOG_LEVEL_DEBUG,            //    DEBUG 级，调试日志
    LOG_LEVEL_INFO,             //    INFO 级，普通的输出日志
    LOG_LEVEL_WARN,             //    WARN 级，警告级别
    LOG_LEVEL_ERROR,            //    ERROR 级，业务错误级别
    LOG_LEVEL_SYSERROR,         //    SYSERROR 级，系统函数调用错误级别
    LOG_LEVEL_FATAL             //    FATAL 级，重大错误级别，整个应用程序直接退出
};

// 使用几个调试宏 (1)__FUNCTION__: 函数名  (2)__TIME__: 运行时间 (3)__LINE__:所在行数 (4)__FILE__: 文件路径，包含文件名
#define LOGT(pszLogMsg)     CAsyncLog::write(LOG_LEVEL_TRACE,__FILE__,__FUNCTION__,__LINE__,const char* pszLogMsg)
#define LOGD(pszLogMsg)     CAsyncLog::write(LOG_LEVEL_TRACE,__FILE__,__FUNCTION__,__LINE__,const char* pszLogMsg)
#define LOGI(pszLogMsg)     CAsyncLog::write(LOG_LEVEL_TRACE,__FILE__,__FUNCTION__,__LINE__,const char* pszLogMsg)
#define LOGW(pszLogMsg)     CAsyncLog::write(LOG_LEVEL_TRACE,__FILE__,__FUNCTION__,__LINE__,const char* pszLogMsg)
#define LOGE(pszLogMsg)     CAsyncLog::write(LOG_LEVEL_TRACE,__FILE__,__FUNCTION__,__LINE__,const char* pszLogMsg)
#define LOGSYSE(pszLogMsg)  CAsyncLog::write(LOG_LEVEL_TRACE,__FILE__,__FUNCTION__,__LINE__,const char* pszLogMsg)
#define LOGF(pszLogMsg)     CAsyncLog::write(LOG_LEVEL_TRACE,__FILE__,__FUNCTION__,__LINE__,const char* pszLogMsg)

class CAsyncLog
{
public:
    //初始化
    static bool init(const char* pszLogFileName);
    //
    static void uninit();

    //输出线程ID号和所在函数签名、行号
    static bool write(short nLevel,const char* pszFileName,const char* pszFuncName,int nLineNo,const char* pszLogMsg);

    //写日志线程方法
    static void writeThreadProc();

private:
    CAsyncLog()=delete;
    ~CAsyncLog()=delete;

    CAsyncLog(const CAsyncLog& rhs)=delete;
    CAsyncLog& operator=(const CAsyncLog& rhs)=delete;

private:
    static std::string                              m_strFileNamePID;               //线程ID
    static std::unique_ptr<std::thread>             m_spWriteThread;                //写入日志的线程
    static std::mutex                               m_mutexWrite;                   //写日志锁
    static std::condition_variable                  m_cvWrite;                      //写条件变量
    static std::string                              m_strPID;                       //进程ID
    static std::list<std::string>                   m_listLinesToWrite;             //待写入的日志列表
    

};


#endif








