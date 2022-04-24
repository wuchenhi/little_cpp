#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

using namespace std;

//void test() 测试
//{
//	Worker* worker = NULL;
//	worker = new Employee(1,"张三",1);
//	worker->showInfo();
//	delete worker;
//	worker = new Manager(2, "李四", 2);
//	worker->showInfo();
//	delete worker;
//	worker = new Boss(3, "王五", 3);
//	worker->showInfo();
//	delete worker;
//}

int main()
{
	WorkerManager Wm;
	int chioce = 0;
	while (true)
	{
		
		Wm.Show_Menu();
		cout << "请输入序号" << endl;
		cin >> chioce;
		switch (chioce)
		{

		case 0: //退出系统
			Wm.exitSystem();
			break;
		case 1: //添加职工
			Wm.Add_Emp();
			Wm.save();
			break;
		case 2: //显示职工
			Wm.Show_Emp();
			break;
		case 3: //删除职工
			Wm.Del_Emp();
			break;
		case 4: //修改职工
			Wm.Mod_Emp();
			break;
		case 5: //查找职工
			Wm.Find_Emp();
			break;
		case 6: //排序职工
			Wm.Sort_Emp();
			break;
		case 7: //清空文件
			Wm.Clean_File();
			break;

		default:
			system("cls");
			break;
		}

	}

	system("pause");
	return 0;
}