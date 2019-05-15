/*
模拟多线程
实现多智能体路径规划
*/
#pragma once
#include "CAgent.h"
#include <time.h>
#include <vector>
#include <fstream>
#include <unordered_map>
/*用于批量处理时的统计 存储CAgentSystem实例信息*/
struct stCAgentSystem
{
	int MAS_id;
	clock_t cost_time;//耗时
	int cost_expand;//总开销
	int conflict_num;//冲突数量
	stCAgentSystem(int MAS_id_in, clock_t cost_time_in,int cost_expand_in,int conflict_num_in) 
		:MAS_id(MAS_id_in),cost_expand(cost_expand_in),cost_time(cost_time_in),conflict_num(conflict_num_in){}
};
class CAgentSystem
{
	CGridMap* gridmap;
	CDistance* distance;

	clock_t begintime;
	clock_t cost_time;//耗时
	int cost_expand;//总开销
	int conflict_num;//冲突数量
	std::unordered_map <int,std::vector<int>> pathpool;//agentid path
	std::vector <CAgent*> Agent_pool;
public:

	CAgentSystem(std::string pathname);
	~CAgentSystem();

	int run();//

	clock_t get_cost_time();//耗时
	int get_cost_expand();//总开销
	int get_conflict_num();//冲突数量

	void print_pathpool_to_Console();

	int resolve_conflicts();//解决冲突
};
inline clock_t CAgentSystem::get_cost_time()
{
	return cost_time;
}

inline int CAgentSystem::get_cost_expand()
{
	return cost_expand;
}

inline int CAgentSystem::get_conflict_num()
{
	return conflict_num;
}
