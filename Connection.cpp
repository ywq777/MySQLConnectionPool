//
// Created by hp-pc on 2023/3/30.
//

#include "Connection.h"
#include <mysql.h>
#include "public.h"
using namespace std;

Connection::Connection()
{
    _conn = mysql_init(nullptr);
}

Connection::~Connection()
{
    if(_conn != nullptr)
        mysql_close(_conn);
}

bool Connection::connect(const string& ip, unsigned short port,
                         const string& username, const string& password, const string& dbname)
{
    MYSQL *p = mysql_real_connect(_conn, ip.c_str(), username.c_str(),
                                  password.c_str(), dbname.c_str(), port, nullptr, 0);
    return p != nullptr;
}

bool Connection::update(const string& sql)
{
    if(mysql_query(_conn, sql.c_str()))
    {
        LOG("更新失败" + sql);
        return false;
    }
    return true;
}

MYSQL_RES *Connection::query(const string& sql)
{
    if(mysql_query(_conn, sql.c_str()))
    {
        LOG("查询失败" + sql);
        return nullptr;
    }
    return mysql_use_result(_conn);
}