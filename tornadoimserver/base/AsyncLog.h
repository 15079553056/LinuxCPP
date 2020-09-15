#ifndef ASYNCLOG_H
#define ASYNCLOG_H

//思路: 新开辟一个线程进行日志写入
//      应该设计为生产消费者模式，有一个队列存储需要写入的日志内容。
//      应该使用事件模型，每次写入线程函数进行阻塞，直到触发事件才进行下去。每触发一次事件，执行一次写入。
//日志应分为的等级: 
//    TRACE 级，方法执行记录
//    DEBUG 级，调试日志
//    INFO 级，普通的输出日志
//    WARN 级，警告级别
//    ERROR 级，业务错误级别
//    SYSERROR 级，系统函数调用错误级别
//    FATAL 级，重大错误级别，整个应用程序直接退出

enum LOG_LEVEL
{
    LOG_LEVEL_TRACE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_SYSERROR,
    LOG_LEVEL_FATAL
};

class CAsyncLog
{
public:
    //初始化
    static bool init(const char* pszLogFileName);
    //
    static void uninit();

    //输出线程ID号和所在函数签名、行号
    static bool write();

private:
    CAsyncLog()=delete;
    ~CAsyncLog()=delete;

    CAsyncLog(const CAsyncLog& rhs)=delete;
    CAsyncLog& operator=(const CAsyncLog& rhs)=delete;

    

    

};


#endif








