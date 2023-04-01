#include <iostream>
#include <string>
using namespace std;
#include "Connection.h"
#include "CommonConnectionPool.h"


int main() {
//    Connection conn;
////    char sql[1024] = {0};
////    sprintf(sql, "insert into user(name, age, sex) values(\"闫\", 24, \"male\")");
//
//    string sql = R"(insert into user(name, age, sex) values("闫", 25, "male"))";
//
//    conn.connect("127.0.0.1", 13306, "root", "abc123", "chat");
//    conn.update(sql);

//    for(int i = 0; i < 5000; i++)
//    {
//        Connection conn;
//        string sql = R"(insert into user(name, age, sex) values("ywq", 25, "male"))";
//        conn.connect("127.0.0.1", 13306, "root", "abc123", "chat");
//        conn.update(sql);
//    }

//    Connection conn;
//    string sql = R"(insert into user(name, age, sex) values("ywq", 25, "male"))";
    clock_t begin = clock();
    CommonConnectionPool *cp = CommonConnectionPool::getConnectionPool();
    for (int i = 0; i < 5000; ++i)
    {
        string sql = R"(insert into user(name, age, sex) values("ywq", 25, "male"))";
        shared_ptr<Connection> sp = cp->getConnection();
        sp->update(sql);
    }
//    thread t1([](){
////        for(int i = 0; i < 1250; i++)
////        {
////            Connection conn;
////            string sql = R"(insert into user(name, age, sex) values("ywq", 25, "male"))";
////            conn.connect("127.0.0.1", 13306, "root", "abc123", "chat");
////            conn.update(sql);
////        }
//        CommonConnectionPool *cp = CommonConnectionPool::getConnectionPool();
//        for (int i = 0; i < 1250; ++i)
//        {
//            string sql = R"(insert into user(name, age, sex) values("ywq", 25, "male"))";
//            shared_ptr<Connection> sp = cp->getConnection();
//            sp->update(sql);
//        }
//    });
//    thread t2([](){
////        for(int i = 0; i < 1250; i++)
////        {
////            Connection conn;
////            string sql = R"(insert into user(name, age, sex) values("ywq", 25, "male"))";
////            conn.connect("127.0.0.1", 13306, "root", "abc123", "chat");
////            conn.update(sql);
////        }
//        CommonConnectionPool *cp = CommonConnectionPool::getConnectionPool();
//        for (int i = 0; i < 1250; ++i)
//        {
//            string sql = R"(insert into user(name, age, sex) values("ywq", 25, "male"))";
//            shared_ptr<Connection> sp = cp->getConnection();
//            sp->update(sql);
//        }
//    });
//    thread t3([](){
////        for(int i = 0; i < 1250; i++)
////        {
////            Connection conn;
////            string sql = R"(insert into user(name, age, sex) values("ywq", 25, "male"))";
////            conn.connect("127.0.0.1", 13306, "root", "abc123", "chat");
////            conn.update(sql);
////        }
//        CommonConnectionPool *cp = CommonConnectionPool::getConnectionPool();
//        for (int i = 0; i < 1250; ++i)
//        {
//            string sql = R"(insert into user(name, age, sex) values("ywq", 25, "male"))";
//            shared_ptr<Connection> sp = cp->getConnection();
//            sp->update(sql);
//        }
//    });
//    thread t4([](){
////        for(int i = 0; i < 1250; i++)
////        {
////            Connection conn;
////            string sql = R"(insert into user(name, age, sex) values("ywq", 25, "male"))";
////            conn.connect("127.0.0.1", 13306, "root", "abc123", "chat");
////            conn.update(sql);
////        }
//        CommonConnectionPool *cp = CommonConnectionPool::getConnectionPool();
//        for (int i = 0; i < 1250; ++i)
//        {
//            string sql = R"(insert into user(name, age, sex) values("ywq", 25, "male"))";
//            shared_ptr<Connection> sp = cp->getConnection();
//            sp->update(sql);
//        }
//    });
//    t1.join();
//    t2.join();
//    t3.join();
//    t4.join();

    clock_t end = clock();
    cout << (end - begin) << "ms" << endl;
    return 0;
}
