#include "ThreadPool.h"

CThreadPool::CThreadPool():
    m_isStarted(false)
{

}

CThreadPool::~CThreadPool()
{
    if (m_isStarted)
    {
        stop();
    }
}


bool CThreadPool::start()
{
    //改变动态数组的容量
    m_threads.reserve(nInitThreadNum);
    for (int i = 0; i < nInitThreadNum; i++)
    {
        m_threads.push_back(new std::thread(std::bind(&CThreadPool::threadLoop, this)));
    }
    m_isStarted = true;

    return true;
}


void CThreadPool::stop()
{
    m_isStarted = false;

    //停止所有线程，并释放资源
    for (std::vector<std::thread*>::iterator it = m_threads.begin(); it != m_threads.end(); it++)
    {
        //回收创建线程的资源
        (*it)->join();
        delete *it;     
    }
    //删除线程数组元素
    m_threads.clear();
}

void CThreadPool::threadLoop()
{
    while (m_isStarted)
    {
        //取出任务
        CWaitTask task = take();
        //执行任务
        task();
    }
}

void CThreadPool::taskEnqueue(const TaskFun& task,void* wParam,void* lParam)
{
    std::lock_guard<std::mutex> lg(m_mutexTask);
    TaskPair taskPair(taskPriorityE::level2, task);
    m_tasks.push(taskPair);
    //唤醒一次写线程
    m_cvTask.notify_one();
}

void CThreadPool::taskEnqueue(const TaskPair& taskPair)
{
    std::lock_guard<std::mutex> lg(m_mutexTask);
    m_tasks.push(taskPair);
    m_cvTask.notify_one();
}


CThreadPool::CWaitTask CThreadPool::take()
{
    std::unique_lock<std::mutex> lg(m_mutexTask);
    while (m_tasks.empty() || !m_isStarted)
    {
        //阻塞，等待被唤醒
        m_cvTask.wait(lg);
    }

    return m_tasks.top().second;
}
