#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>



class CThreadPool
{
public:
    static const int nInitThreadNum = 3;
    enum taskPriorityE
    {
        level0,
        level1,
        level2
    };
    //函数对象
    typedef std::function<void(void*,void*)> TaskFun;
    //
    typedef std::pair<taskPriorityE, TaskFun> TaskPair;



    class CWaitTask
    {
    public:
        CWaitTask(TaskFun& task, void* wParam, void* lParam):
            m_task(task),
            m_wParam(wParam),
            m_lParam(lParam)
        {

        }

    private:
        TaskFun m_task;    //要执行的任务
        void* m_wParam;    //参数
        void* m_lParam;    //参数

    };

public:
    bool start();
    void stop();

    //任务入队
    void taskEnqueue(const TaskFun&,void* wParam,void* lParam);
    void taskEnqueue(const TaskPair&);

    CThreadPool();
    ~CThreadPool();

private:

    CThreadPool(const CThreadPool& rhs) = delete;
    CThreadPool& operator=(const CThreadPool& rhs) = delete;

    void threadLoop();
    //从任务队列中取出任务，优先取优先级高的
    TaskFun take();
private:
    struct TaskPriorityCompare
    {
        bool operator()(const CThreadPool::TaskPair p1, const CThreadPool::TaskPair p2)
        {
            //first 的小值优先
            return p1.first > p2.first;
        }
    };

    //使用优先队列
    typedef std::priority_queue<TaskPair, std::vector<TaskPair>, TaskPriorityCompare> Tasks;

    std::vector<std::thread*> m_threads;  //线程数组    
    CWaitTask m_tasks;  //任务队列
    std::mutex m_mutexTask;  //任务队列锁
    std::condition_variable m_cvTask;  //任务条件变量
    bool m_isStarted;  //是否运行
};

#endif // !THREADPOOL_H






