#ifndef DIRECTORYHELPER_H
#define DIRECTORYHELPER_H

#include <string>
#include <mutex>

class CDirectoryHelper
{
public:
    //目录是否存在
    static bool DirIsExist(const std::string& strDirPath);
    //创建目录(多级创建)
    static int32_t DirCreate(const std::string& strDirPath);

private:
    //禁止构造函数
    CDirectoryHelper();
    ~CDirectoryHelper();
    //禁止拷贝构造函数
    CDirectoryHelper(const CDirectoryHelper& rhs)=delete;
    CDirectoryHelper& operator=(const CDirectoryHelper& rhs)=delete;

private:
    static std::mutex                    m_mutexCreateDir;                    //新建目录锁

};

#endif
