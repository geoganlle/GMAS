#pragma once
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include "CGridMap.h"
#include "CBfs.h"
#include "CAgent.h"
#include "CAgentSystem.h"
using namespace std;
class CGlobalFunction
{
public:

	CGlobalFunction();
	~CGlobalFunction();
};
vector<int> string_spilt_to_int(const std::string& string_input);
bool resolve_self_loop(vector<int>&int_vector);
void get_gorge_test();//����map��get_gorge����
void test1();//����map bfs agent
void test2();//����agentsystem
void test3();//���Զ��agentsystem
void test4();
void runmas1();
void runmas2();