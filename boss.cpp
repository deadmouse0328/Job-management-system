#include "boss.h"

using namespace std;

//Constructor:
Boss::Boss(int id, string name, int d_ID)
{
    this->m_ID = id;
    this->m_Name = name;
    this->m_dept_ID = d_ID;
}

//显示个人信息：
void Boss::showInfo()
{
    cout << "职工编号： " << this->m_ID
         << "\t职工姓名： " << this->m_Name
         << "\t职工部门： " << this->getDeptName()
         << "\t岗位职责： 管理公司所有的事务；"
         << endl;
}

string Boss::getDeptName() {
    return string ("老板");
}
