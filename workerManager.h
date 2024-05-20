#ifndef EXERCISE2___WORKERMANAGER_H
#define EXERCISE2___WORKERMANAGER_H

#include <iostream>
#include <fstream>

#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#define FILENAME "empFile.txt"

using namespace std;

class WorkerManager
{
public:

    WorkerManager();

    //show menu:
    void Show_Menu();

    //退出系统：
    void exitSystem();

    //记录职工人数：
    int m_EmpNum;

    //职工数组指针：
    worker ** m_EmpArray;

    //添加职工函数：
    void Add_Emp();

    //保存文件:
    void save();

    //判读文件是否为空：
    bool m_FileIsEmpty;

    //统计文件中的人数：
    int get_EmpNum();

    //初始化员工：
    void init_Emp();

    //显示职工：
    void Show_Emp();

    //删除员工：
    void Del_Emp();

    //判断员工是否存在。如果存在，返回具体位置；如果不存在，返回-1；
    int WorkerExist(int id);

    //修改职工:
    void Mod_Emp();

    //查找职工：
    void Find_Emp();

    //按照编号排序：
    void Sort_Emp();

    //清空文件：
    void Clean_File();


    ~WorkerManager();
};

#endif
