//


#include "workerManager.h"
using namespace std;


WorkerManager::WorkerManager()
{
    //不能每次打开文件都清空，因此要分成：1. 文件不存在；2. 文件存在无数据；3. 文件存在有数据；

    //1. 文件不存在：
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    if (! ifs.is_open())
    {
        cout << "文件不存在! " << endl;

        //初始化属性：
        this->m_EmpNum = 0;
        //初始化数组指针：
        this->m_EmpArray = NULL;
        //初始化bool:
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    //2. 文件存在无数据；

    //此方法可以读取文件是否为空：
    char ch;
    ifs >> ch;

    if (ifs.eof())
    {
        //文件为空：
        cout << "文件为空！" << endl;

        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    //3. 文件存在有数据；
    int num = this->get_EmpNum();
    cout << "职工人数为： " << num << endl;
    this->m_EmpNum = num;

    //开辟空间：
    this->m_EmpArray = new worker * [this->m_EmpNum];
    //将文件中的数据， 存到数组中：
    this->init_Emp();

    //test:

//    for (int i = 0; i < this->m_EmpNum; i++)
//    {
//        cout << "职工编号： " << this->m_EmpArray[i]->m_ID << " "
//             << "姓名： " << this->m_EmpArray[i]->m_Name << " "
//             << "部门： " << this->m_EmpArray[i]->m_dept_ID << endl;
//    }

};

void WorkerManager::Show_Menu()
{
    cout << endl;
    cout << "********************************" << endl;
    cout << "********* 0.退出管理程序 *********" << endl;
    cout << "********* 1.增加职工信息 *********" << endl;
    cout << "********* 2.显示职工信息 *********" << endl;
    cout << "********* 3.删除离职职工 *********" << endl;
    cout << "********* 4.修改职工信息 *********" << endl;
    cout << "********* 5.查找职工信息 *********" << endl;
    cout << "********* 6.按照编号排序 *********" << endl;
    cout << "********* 7.清空所有文档 *********" << endl;
    cout << "********************************" << endl;
    cout << endl;
}

//1. 退出系统：
void WorkerManager::exitSystem()
{
    cout << "欢迎下次使用！" << endl;
    //system("pause");
    exit(0);
}

//添加职工：
void WorkerManager::Add_Emp()
{
    cout << "请输入添加职工的数量：" << endl;
    int addNum = 0; //保存用户的输入数量；
    cin >> addNum;

    if (addNum > 0)
    {
        //Add:

        //calculate new space size:
        // new space number = before number + added number
        int newSize = this->m_EmpNum + addNum;

        //开辟新空间：
        worker ** newSpace = new worker*[newSize];

        //remove before data to new data:
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        //批量添加新数据：
        for (int i = 0; i < addNum; i++)
        {
            //编号，姓名，部门选择:
            int id;
            string name;
            int dSelect;

            cout << "请输入第 " << i + 1 << " 个新员工的编号： " << endl;
            cin >> id;

            cout << "请输入第 " << i + 1 << " 个新员工的姓名： " << endl;
            cin >> name;

            cout << "请选择新员工的岗位： " << endl;
            cout << "1. 普通职工 " << endl;
            cout << "2. 经理 " << endl;
            cout << "3. 老板 " << endl;
            cin >> dSelect;

            worker * Worker = NULL;
            switch (dSelect) {
                case 1:
                    Worker = new Employee(id, name, 1);
                    break;

                case 2:
                    Worker = new Manager(id, name, 2);
                    break;

                case 3:
                    Worker = new Boss(id, name, 3);
                    break;

                default:
                    break;
            }
            //将创建的职工职责，保存到数组中：
            newSpace[this->m_EmpNum+ i] = Worker;

        }
        //释放原有的空间：
        delete [] this->m_EmpArray;

        //更改新空间的指向：
        this->m_EmpArray = newSpace;

        //更新职工人数：
        this->m_EmpNum = newSize;

        //提示职工不为空标志：
        this->m_FileIsEmpty = false;


        //提示，添加成功：
        cout << "成功添加了" << addNum << "名新职工！" << endl;

        //成功添加后，保存数据到文件中：
        this->save();


    } else {
        cout << "输入数据有误." << endl;
    }

    //按任意键清屏，然后回到上级目录：
    cout << "Press Enter to continue...";
    string dummy;
    getline(std::cin, dummy);

    system("clear");

}

void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out); //用输出的方式打开文件， 写文件：

    //将每个人的数据保存到文件中：
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_ID << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_dept_ID << endl;
    }

    //close:
    ofs.close();
}

//统计文件中的人数：
int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        //统计人数变量；
        num++;
    }
    return num;
}

void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int index = 0;

    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        worker * Worker = NULL;

        if (dId == 1)//普通职工
        {
            Worker = new Employee(id, name, dId);
        }
        else if (dId == 2)
        {
            Worker = new Manager(id, name, dId);
        } else
        {
            Worker = new Boss(id, name, dId);
        }

        this->m_EmpArray[index] = Worker;
        index++;
    }

    //关闭文件：
    ifs.close();

}

//显示职工：
void WorkerManager::Show_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "当前文件为空, 或者文件不存在，请检查。" << endl;


        system("clear");
        return;
    } else
    {
        for (int i = 0; i < m_EmpNum; i++)
        {
            //use polymorphism:
            this->m_EmpArray[i]->showInfo();
        }

        //按任意键清屏，然后回到上级目录：
        cout << "Press Enter to continue...";
        string dummy;
        getline(std::cin, dummy);

        system("clear");

    }
}

//删除员工：
void WorkerManager::Del_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在，或记录为空！" << endl;
    } else
    {
        cout << "请输入想要删除的编号： " << endl;
        int id = 0;
        cin >> id;

        int index = this->WorkerExist(id);

        if (index != -1)
        {
            //职工存在，并且要删除掉index位置上的职工；
            for (int i = index; i < this->m_EmpNum - 1; i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];

            }
            //update the total employee number;
            this->m_EmpNum--;

            //update to file:
            this->save();

            cout << "删除成功！ " << endl;

        } else {
            //ID doesn't exist;
            cout << "删除失败，未找到员工！" << endl;
        }

        //按任意键清屏，然后回到上级目录：
        cout << "Press Enter to continue...";
        string dummy;
        getline(std::cin, dummy);

        system("clear");
    }

}

int WorkerManager::WorkerExist(int id)
{
    int index = -1;

    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if (this->m_EmpArray[i]->m_ID == id)
        {
            //find:
            index = i;
            break;
        }
    }

    return index;
}

//修改职工:
void WorkerManager::Mod_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在，或者为空！" << endl;
    } else
    {
        cout << "请输入修改职工的编号：" << endl;
        int id;
        cin >> id;

        int id_check = this->WorkerExist(id);

        //id_check == ret
        if (id_check != -1)
        {
            //找到编号：

            //先释放堆区内存：
            //delete this->m_EmpArray[id_check];
            //(测试，释放内存后会报错;)

            int new_id = 0;
            string newName = "";
            int dSelect = 0;

            cout << "查到： " << id << "号职工，请输入新职工号： " << endl;
            cin >> new_id;

            cout << "请输入新的姓名： " << endl;
            cin >> newName;

            cout << "请输入新的岗位： " << endl;
            cout << "1. 普通职工；" << endl;
            cout << "2. 经理；" << endl;
            cout << "3. 老板；" << endl;

            cin >> dSelect;

            worker * Worker = NULL;

            switch (dSelect) {
                case 1:
                    Worker = new Employee(new_id, newName, dSelect);
                    break;
                case 2:
                    Worker = new Manager(new_id, newName, dSelect);
                    break;
                case 3:
                    Worker = new Boss(new_id, newName, dSelect);
                    break;
                default:
                    break;
                
            }
            //更新数据到数组中；
            this->m_EmpArray[id_check] = Worker;

            cout << "修改成功！" << endl;

            //保存到文件中；
            this->save();


        } else
        {
            //没找到：
            cout << "查无此人！" << endl;

            //按任意键清屏，然后回到上级目录：
            //cout << "Press Enter to continue...";
            string dummy;
            getline(std::cin, dummy);

            system("clear");

        }
    }

    //按任意键清屏，然后回到上级目录：
    cout << "Press Enter to continue...";
    string dummy;
    getline(std::cin, dummy);

    system("clear");
}

//查找职工：
void WorkerManager::Find_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在，或者记录为空！" << endl;
    } else
    {
        cout << "请输入查找的方式(1 or 2)：" << endl;
        cout << "1. 职工编号查找 " << endl;
        cout << "2. 职工姓名查找 " << endl;

        int select;
        cin >> select;

        if (select == 1)
        {
            //按照编号查找：
            cout << "请输入查找职工的编号：" << endl;
            int id;
            cin >> id;

            int id_check = WorkerExist(id);
            if (id_check != -1)
            {
                //success:
                cout << "查找成功，职员信息如下： " << endl;
                this->m_EmpArray[id_check]->showInfo();
            } else
            {
                cout << "查无此人！" << endl;
            }


        } else if (select == 2)
        {
            //按照姓名查找:
            cout << "请输入查找的姓名: " << endl;

            string name;
            cin >> name;

            //加入是否查到的标志, 默认为“没找到”
            bool flag = false;

            for (int i = 0; i < m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_Name == name)
                {
                    //success
                    cout << "查找成功，职工编号为： " << this->m_EmpArray[i]->m_ID << endl;
                    cout << "职工信息如下： " << endl;

                    //设定为“找到”
                    flag = true;

                    //显示信息：
                    this->m_EmpArray[i]->showInfo();
                }
            }
            if (flag == false)
            {
                cout << "查无如此！" << endl;
            }

        } else
        {
            //其他输入：
            cout << "输入选项有误，请重新输入！" << endl;

        }
    }

    //按任意键清屏，然后回到上级目录：
    cout << "Press Enter to continue...";
    string dummy;
    getline(std::cin, dummy);

    system("clear");
}

//按照编号排序：
void WorkerManager::Sort_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在，或记录为空！" << endl;

        cout << "Press Enter to continue...";
        string dummy;
        getline(std::cin, dummy);

        system("clear");

    } else
    {
        cout << "请选择排序的方式(1 or 2)： " << endl;
        cout << "1. 职工号升序 " << endl;
        cout << "2. 职工号降序 " << endl;

        int select = 0;
        cin >> select;

        for (int i = 0; i < m_EmpNum; i++)
        {
            //声明最小值 或 最大值 下标:
            int minOrMax = i;

            for (int j = i + 1; j < this->m_EmpNum; j++) {
                //升序
                if (select == 1) {

                    if (this->m_EmpArray[minOrMax]->m_ID  > this->m_EmpArray[j]->m_ID)
                    {
                        //当前还不是最小值，更新下标：
                        minOrMax = j;

                    }
                } else //降序
                {
                    if (this->m_EmpArray[minOrMax]->m_ID < this->m_EmpArray[j]->m_ID)
                    {
                        minOrMax = j;
                    }
                }
            }
            //判断一开始认定的 最小值或最大值 是不是计算的 最小值或最大值, 如果不是，交换数据:

            if (i != minOrMax)
            {
                worker * temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
                this->m_EmpArray[minOrMax] = temp;
            }

        }

        cout << "排序成功！排序后的结果为: " << endl;
        this->save();
        this->Show_Emp(); //展示所有职工；


    }
}

//清空文件：
void WorkerManager::Clean_File()
{
    cout << "确定要清空吗？(1 or 2) " << endl;
    cout << "1. 确定 " << endl;
    cout << "2. 返回 " << endl;

    int select;
    cin >> select;

    if (select == 1)
    {
        //清空文件：
        ofstream ofs(FILENAME, ios::trunc); //删除文件后创建；
        ofs.close();

        if(this->m_EmpArray != NULL)
        {
            //删除堆区的每个职工对象：
            for (int i = 0; i < m_EmpNum; i++)
            {
                delete this->m_EmpArray[i];
                m_EmpArray[i] = NULL;
            }

            //删除堆区数组指针：
            delete[] this->m_EmpArray;
            this->m_EmpArray = nullptr;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true;

            //finish!
        }
        cout << "清空成功！" << endl;



    } else if (select == 2)
    {

    } else
    {
        cout << "输入错误，请重试！" << endl;
    }

    cout << "Press Enter to continue...";
    string dummy;
    getline(std::cin, dummy);

    system("clear");
}




WorkerManager::~WorkerManager()
{
    if (this->m_EmpArray != NULL)
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            if (this->m_EmpArray[i] != NULL)
            {
                delete this->m_EmpArray[i];
            }
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}
