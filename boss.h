#ifndef EXERCISE2___BOSS_H
#define EXERCISE2___BOSS_H
#include "worker.h"
using namespace std;

//老板类：
class Boss : public worker
{
public:
    Boss(int id, string name, int d_ID);

    //显示个人信息：
    virtual void showInfo();

    //获取岗位名称:
    virtual string getDeptName();


};


class boss {

};


#endif //EXERCISE2___BOSS_H
