#ifndef CLONE_CONNECTION_H
#define CLONE_CONNECTION_H
#include <mysql.h>
#include "public.h"
#include <string>
#include <ctime>
using namespace std;

class Connection
{
public:
    // 初始化数据库连接
    Connection();

    // 释放数据库连接资源
    ~Connection();

    // 连接数据库
    bool connect(const string& ip,
                 unsigned short port,
                 const string& username,
                 const string& password,
                 const string& dbname);

    // 更新操作
    bool update(const string& sql);

    //查询操作
    MYSQL_RES* query(const string& sql);

    void refreshAliveTime() {_alivetime = clock();}

    clock_t getAliveTime() {return clock() - _alivetime;}

private:
    MYSQL *_conn; //表示和MySQL Server的一条连接
    clock_t _alivetime; // 进入空闲状态的起始时间
};


#endif //CLONE_CONNECTION_H
