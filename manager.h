#ifndef EXERCISE2___MANAGER_H
#define EXERCISE2___MANAGER_H
#include "worker.h"
using namespace std;

//经理类：
class Manager : public worker
{
public:
    //constructor
    Manager(int id, string name, int d_ID);

    //显示个人信息：
    virtual void showInfo();

    //获取岗位名称：
    virtual string getDeptName();

};

#endif //EXERCISE2___MANAGER_H
