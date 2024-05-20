#include <iostream>
#include "workerManager.h"
using namespace std;

//#include "worker.h"
//#include "employee.h"
//#include "manager.h"
//#include "boss.h"

int main() {

//    //测试代码：
//    worker * worker = NULL;
//
//    worker = new Employee(1, "Jessie", 1);
//    worker->showInfo();
//    //delete worker;
//
//    worker = new Manager(2, "Walter", 2);
//    worker->showInfo();
//    //delete worker;
//
//    worker = new Boss(2, "Gus", 3);
//    worker->showInfo();
//    //delete worker;


    //实例化管理者对象：
    WorkerManager wm;

    int choice = 0; //用来存储用户的选项：
    while (true)
    {
        wm.Show_Menu();

        cout << "请输入你的选择：" << endl;
        cin >> choice; //接受用户的选项；
        cin.clear();
        cin.ignore();


        switch (choice) {
            case 0:   //退出系统
            wm.exitSystem();
                break;
            case 1:   //增加职工
            wm.Add_Emp();
                break;
            case 2:   //显示职工
            wm.Show_Emp();
                break;
            case 3:   //删除职工
            wm.Del_Emp();
                break;
            case 4:   //修改职工
            wm.Mod_Emp();
                break;
            case 5:   //查找职工
            wm.Find_Emp();
                break;
            case 6:   //排序职工
            wm.Sort_Emp();
                break;
            case 7:   //清空文档
            wm.Clean_File();
                break;
            default:  //清屏
                //system("cls");
                break;


            
        }


    }




    //调用展示菜单的成员函数：

    //system("pause");
    //return 0;


    // case 3: check worker exist test code:
//    {
//        int ret = wm.WorkerExist(520);
//
//        if (ret != -1) {
//            cout << "职工存在。" << endl;
//
//        } else {
//            cout << "职工不存在！" << endl;
//        }
//        break;
//    }
}
