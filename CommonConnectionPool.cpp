#include "CommonConnectionPool.h"
#include "public.h"
using namespace std;

CommonConnectionPool* CommonConnectionPool::getConnectionPool()
{
    static CommonConnectionPool pool;
    return &pool;
}

bool CommonConnectionPool::loadConfigFile()
{
    FILE* pf = fopen("mysql.ini", "r");
    if(pf == nullptr)
    {
        LOG("mysql.ini file is not exist!");
        return false;
    }

    while(!feof(pf))
    {
        char line[1024] = {0};
        fgets(line, 1024, pf);
        string str = line;
        int idx = str.find('=', 0);
        if(idx == -1)
        {
            continue;
        }
        int endix = str.find('\n', idx);
        string key = str.substr(0, idx);
        string value = str.substr(idx +1, endix-idx-1);

        if(key == "ip")
        {
            _ip = value;
        }
        else if(key == "port")
        {
            _port = atoi(value.c_str());
        }
        else if(key == "username")
        {
            _username = value;
        }
        else if(key == "password")
        {
            _password = value;
        }
        else if(key == "dbname")
        {
            _dbname = value;
        }
        else if(key == "initSize")
        {
            _initSize = atoi(value.c_str());
        }
        else if(key == "maxSize")
        {
            _maxSize = atoi(value.c_str());
        }else if(key == "maxIdleTime")
        {
            _maxIdleTime = atoi(value.c_str());
        }else if(key == "connectionTimeout")
        {
            _connectionTimeout = atoi(value.c_str());
        }
    }
    return true;
}

// 连接池构造
CommonConnectionPool::CommonConnectionPool()
{
    if(!loadConfigFile())
    {
        return;
    }

    for (int i = 0; i < _initSize; ++i)
    {
        Connection* p = new Connection();
        p->connect(_ip, _port, _username, _password, _dbname);
        p->refreshAliveTime();
        _connectionQue.push(p);
        _connectionCnt++;
    }

    // 启动一个线程，作为连接生产者
    thread produce(std::bind(&CommonConnectionPool::produceConnectionTask, this));
    produce.detach();
    // 启动一个线程，清理连接
    thread scanner(std::bind(&CommonConnectionPool::scannerConnectionTask, this));
    scanner.detach();
}

// 运行在独立的线程中，专门生产新连接
void CommonConnectionPool::produceConnectionTask()
{
    while(true)
    {
        unique_lock<mutex> mtx(_queueMutex);
        while (!_connectionQue.empty())
        {
            cv.wait(mtx);
        }
        if(_connectionCnt < _maxSize)
        {
            Connection* p = new Connection();
            p->connect(_ip, _port, _username, _password, _dbname);
           p->refreshAliveTime();
            _connectionQue.push(p);
            _connectionCnt++;
        }
        cv.notify_all();
    }
}

// 从连接池中获取一个可用的空闲连接
shared_ptr<Connection> CommonConnectionPool::getConnection()
{
    unique_lock<mutex> mtx(_queueMutex);
    while(_connectionQue.empty())
    {
        // 判断是被唤醒，还是等待超时
        if(cv_status::timeout == cv.wait_for(mtx, chrono::milliseconds(_connectionTimeout)))
        {
            if(_connectionQue.empty())
            {
                LOG("获取空闲连接超时...获取连接失败");
                return nullptr;
            }
        }
    }
    shared_ptr<Connection> sp(_connectionQue.front(),
                              [&](Connection* pcon){
        unique_lock<mutex> mtx(_queueMutex); // 保证队列线程安全
        _connectionQue.push(pcon);
    });
    _connectionQue.pop();
    cv.notify_all();
    return sp;
}


void CommonConnectionPool::scannerConnectionTask()
{
    while(true)
    {
        this_thread::sleep_for(chrono::seconds(_maxIdleTime));
        unique_lock<mutex> mtx(_queueMutex);
        while (_connectionCnt > _initSize)
        {
            Connection* p = _connectionQue.front();
            if(p->getAliveTime() < _maxIdleTime)
            {
                break;
            }
            else
            {
                _connectionQue.pop();
                _connectionCnt--;
                delete p;
            }
        }
    }
}