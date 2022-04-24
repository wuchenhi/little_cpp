#pragma once
#include <iostream>
#include "worker.h"

using namespace std;

class Employee : public Worker 
{
public:
	Employee(int id, string name, int dId);
	//如果override覆盖基类的虚函数而实际未做到，报错 
	virtual void showInfo() override; 
	virtual string getDeptName() override;
	
};
