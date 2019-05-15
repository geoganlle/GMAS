#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "CGridMap.h"
#include "CBfs.h"
#include "CAgent.h"
#include "CAgentSystem.h"
using namespace std;
class CGlobalFuntion
{
public:

	CGlobalFuntion();
	~CGlobalFuntion();
};
vector<int> string_spilt_to_int(const std::string& string_input);
void test1();//≤‚ ‘map bfs agent
void test2();//≤‚ ‘agentsystem