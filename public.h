//
// Created by hp-pc on 2023/3/30.
//

#ifndef CLONE_PUBLIC_H
#define CLONE_PUBLIC_H
#include <iostream>
using namespace std;

#define LOG(str) \
    cout << "My LOG: " << __FILE__ << ":" << __LINE__ << ":" \
    __TIMESTAMP__ << ":" << str << endl;
#endif //CLONE_PUBLIC_H
