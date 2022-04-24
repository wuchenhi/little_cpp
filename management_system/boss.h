#pragma once
#include<iostream>
#include "worker.h"

using namespace std;

//boss类
class Boss :public Worker
{
public:

	Boss(int id, string name, int dId);

	//显示个人信息
	virtual void showInfo() override;

	//获取职工岗位名称
	virtual string getDeptName() override;
};
