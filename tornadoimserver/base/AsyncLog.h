#ifndef ASYNCLOG_H
#define ASYNCLOG_H



class CAsyncLog
{
public:
    //输出线程ID号和所在函数签名、行号
    static bool output();

private:
    CAsyncLog()=delete;
    ~CAsyncLog()=delete;

    CAsyncLog(const CAsyncLog& rhs)=delete;
    CAsyncLog& operator=(const CAsyncLog& rhs)=delete;

    

    

};


#endif








