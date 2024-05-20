#ifndef EXERCISE2___EMPLOYEE_H
#define EXERCISE2___EMPLOYEE_H
#include "worker.h"

using namespace std;

//普通员工文件：

class Employee : public worker
{
public:
    Employee(int id, string name, int d_ID);

    //显示个人信息：
    virtual void showInfo();

    //获取岗位名称：
    virtual string getDeptName();

    //~Employee();

};

#endif //EXERCISE2___EMPLOYEE_H
