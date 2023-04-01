//
// Created by hp-pc on 2023/3/30.
//

#ifndef CLONE_COMMONCONNECTIONPOOL_H
#define CLONE_COMMONCONNECTIONPOOL_H
#include <string>
#include <queue>
#include <mutex>
#include <atomic>
#include <thread>
#include <memory>
#include <functional>
#include <condition_variable>
#include "Connection.h"
using namespace std;

class CommonConnectionPool
{
public:
    static CommonConnectionPool* getConnectionPool();

    // 从连接池中获取一个可用的空闲连接
    shared_ptr<Connection> getConnection();

private:
    CommonConnectionPool();

    bool loadConfigFile();

    // 运行在独立的线程中，专门生产新连接
    void produceConnectionTask();

    void scannerConnectionTask();

    string _ip;
    unsigned short _port{};
    string _username;
    string _password;
    string _dbname;
    int _initSize{};
    int _maxSize{};
    int _maxIdleTime{}; // 最大空闲时间
    int _connectionTimeout{}; // 获取连接超时

    queue<Connection*> _connectionQue;
    mutex _queueMutex;
    atomic_int _connectionCnt;
    condition_variable cv; // 生产消费线程的通信
};

#endif //CLONE_COMMONCONNECTIONPOOL_H
