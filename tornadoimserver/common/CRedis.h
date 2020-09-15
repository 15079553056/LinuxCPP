#ifndef CREDIS_H
#define CREDIS_H

class CRedis
{
public:
    CRedis();
    ~CRedis();


private:
    //禁止拷贝、赋值
    CRedis(const CRedis&);
    CRedis& operator =(const CRedis&);

   //服务器连接
   bool connectSvr(const char* pszIp,int nPort,unsigned int nTimeout=1500); 
   //断开连接
   void disconnectSvr();


    


};


#endif


