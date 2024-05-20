#ifndef EXERCISE2___WORKER_H
#define EXERCISE2___WORKER_H

#include <iostream>
#include <string>
using namespace std;


class worker {
public:

    //显示个人信息：
    virtual void showInfo() = 0;

    //获取岗位名称：
    virtual string getDeptName() = 0;

    //职工编号
    int m_ID;

    //职工姓名
    basic_string<char> m_Name;

    //部门编号
    int m_dept_ID;

};


#endif //EXERCISE2___WORKER_H
