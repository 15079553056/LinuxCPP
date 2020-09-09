#include "DirectoryHelper.h"

#ifdef _WIN32
#include <io.h>
#include <direct.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

#ifdef WIN32
#define ACCESS(fileName,accessMode) _access(fileName,accessMode)
#define MKDIR(path) _mkdir(path)
#else 
#define ACCESS(fileName,accessMode) access(fileName,accessMode)
#define MKDIR(path) mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif

#define MAX_PATH_LEN 256

//初始化静态变量
std::mutex CDirectoryHelper::m_mutexCreateDir;

/*
* Description: 创建目录(多级创建)
* In Param strDirPath: 目录路径
* Return: -1    创建失败
*         0     目录已经存在
*         1     创建成功
*/
int32_t CDirectoryHelper::DirCreate(const std::string& strDirPath)
{
    std::lock_guard<std::mutex> lock(m_mutexCreateDir);
    if(DirIsExist(strDirPath))
    {
        return 0;
    }
    
    uint32_t dirPathLen=strDirPath.length();
    if(dirPathLen>MAX_PATH_LEN)
    {
        return -1;
    }
    
    char tmpDirPath[MAX_PATH_LEN]={0};
    for(size_t i=0;i<dirPathLen;i++)
    {
        tmpDirPath[i]=strDirPath[i];
        if(tmpDirPath[i]=='\\' || tmpDirPath[i]=='/')
        {
            if(ACCESS(tmpDirPath,0)!=0)
            {
                int32_t ret=MKDIR(tmpDirPath);
                if(ret!=0)
                {
                    return false;
                }
            }
        }
    }

    return 1;
}

/**
* Description: 目录是否存在
* In Param strDirPath: 文件目录
* return: 
*/
bool CDirectoryHelper::DirIsExist(const std::string& strDirPath)
{
    if(ACCESS(strDirPath.c_str(),0)!=0)
    {
        return false;
    }
    else
    {
        return true;
    }   

}
















