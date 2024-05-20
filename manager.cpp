#include "manager.h"

//constructor
Manager::Manager(int id, string name, int d_ID)
{
    this->m_ID = id;
    this->m_Name = name;
    this->m_dept_ID = d_ID;
}

//显示个人信息：
void Manager::showInfo()
{
    cout << "职工编号： " << this->m_ID
         << "\t职工姓名： " << this->m_Name
         << "\t职工部门： " << this->getDeptName()
         << "\t岗位职责： 完成老板交给的任务，并且下发任务给普通员工；"
         << endl;

}

//获取岗位名称：
string Manager::getDeptName()
{
    return string ("经理");
}