#pragma once
#include <iostream>
#include "worker.h"
#include <fstream>

#define FILENAME "empFile.txt"

using namespace std;

class WorkerManager 
{
public:
	WorkerManager();
	void Show_Menu();
	void exitSystem();
	void Add_Emp();
	void save();
	int get_EmpNum();
	void init_Emp();
	void Show_Emp();
	void Del_Emp();
	int IsExist(int id);
	void Mod_Emp();
	void Find_Emp();
	void Sort_Emp();
	void Clean_File();
	~WorkerManager();
	
	int m_EmpNum;
	bool m_FileIsEmpty;
	Worker** m_EmpArray;
};