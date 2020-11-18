#include "ConfigFileReader.h"
#include <stdio.h>
#include <string.h>

CConfigFileReader::CConfigFileReader(const char* pszFilePath)
{
    loadFile(pszFilePath);
}


char* CConfigFileReader::getConfVal(const char* pszName)
{
    if(!m_bIsLoadOK)
    {
        return NULL;
    }

    char* val=NULL;    
    std::map<std::string,std::string>::iterator it=m_mapConfig.find(pszName);
    if(it!=m_mapConfig.end())
    {
        val=(char*)it->second.c_str();
    }

    return val;
}

bool CConfigFileReader::setConfVal(const char* pszName,const char* pszVal)
{
    if(!m_bIsLoadOK)
    {
        return false;
    }

    std::map<std::string,std::string>::iterator it=m_mapConfig.find(pszName);
    if(it!=m_mapConfig.end())
    {
        it->second=pszVal;
    }
    else
    {
        m_mapConfig.insert(std::make_pair(pszName,pszVal));    
    }
    
    if(writeFile()>=0)
    {
        return true;
    }
    else
    {
        return false;
    }  
}



/*
* 
*/
void CConfigFileReader::loadFile(const char* pszFilePath)
{
    m_bIsLoadOK=false;
    m_strConfigPath.clear();
    m_strConfigPath.append(pszFilePath);
    //以只读方式打开文件
    FILE* fp=fopen(pszFilePath,"r");
    if(fp==NULL)
    {
        return;
    }

    char buf[256];
    for(;;)
    {
        memset(buf,'\0',256);
        //按行读取
        char* p=fgets(buf,256,fp);
        if(p==NULL)
        {
            break;
        }

        size_t len=strlen(buf);
        if(buf[len-1]=='\n')
        {
            buf[len-1]='\0';
        }

        //如果是以 # 开头的注释，则忽略 
        char* ch=strchr(buf,'#');
        if(ch==NULL)
        {
            //*ch='\0';
            continue;
        }

        if(strlen(buf)==0)
        {
            continue;
        }

        char* pIdx=strchr(buf,'=');
        if(pIdx==NULL)
        {
            continue;
        }

        *pIdx='\0';
        char* key=trimSpace(buf);
        char* val=trimSpace(pIdx+1);
        if(key && val)
        {
            m_mapConfig.insert(std::make_pair(key,val));
        }
    }
    
    fclose(fp);
    m_bIsLoadOK=true;
}

int CConfigFileReader::writeFile()
{
    //以只读方式打开配置文件
    FILE* fp=fopen(m_strConfigPath.c_str(),"w");
    if(fp==NULL)
    {
        return -1;
    }

    char szPaire[128];
    for(std::map<std::string,std::string>::iterator it=m_mapConfig.begin();it!=m_mapConfig.end();it++)
    {
        memset(szPaire,'\0',128);
        snprintf(szPaire,sizeof(szPaire),"%s=%s\n",it->first.c_str(),it->second.c_str());
        //写入配置文件,返回值要与第3个参数一致，否则出错
        size_t ret=fwrite(szPaire,strlen(szPaire),1,fp);
        if(ret!=1)
        {
            fclose(fp);
            return -1;
        }
    }
    fclose(fp);
    return 0;
}

char* CConfigFileReader::trimSpace(char* pszName)
{
    char* start_pos=pszName;
    while((*start_pos==' ')||(*start_pos=='\t')||(*start_pos=='\r'))
    {
        start_pos++;
    }

    if(strlen(start_pos)==0)
    {
        return NULL;
    }

    char* end_pos=pszName+strlen(pszName)-1;
    while((*end_pos==' ')||(*end_pos=='\t')||(*end_pos)=='\t')
    {
        *end_pos='\0';
        end_pos--;
    }
    //
    int len=(int)(end_pos-start_pos)+1;
    if(len<=0)
    {
        return NULL;
    }

    return start_pos;
}




