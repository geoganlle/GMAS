#pragma once
#include "CGridMap.h"
#include "CBfs.h"
#include "CDistance.h"
#include<vector>
#include <map>

constexpr auto MAX_SEARCH_COUNT = 10000;

struct stSearch_Node {
	stPoint location;
	int fn;
	int gn;
	int hn;
	int agentid;
	int dir_to_parent;
	stSearch_Node(stPoint location_i= stPoint(),int agentid_i=0, int gn_i=0, int hn_i=0,int dir_to_parent_i=DIM)
		:location(location_i),agentid(agentid_i), gn(gn_i), hn(hn_i), dir_to_parent(dir_to_parent_i){ fn = gn + hn; };
};

class CAgent
{
	//const static int DIM_X;
	int agentid;
	stPoint init;
	stPoint goal;
	std::vector <int> path_hash;
	CGridMap* gridmap;
	CDistance* cdistance;

	std::vector <stSearch_Node> search_node_pool;//手动维护 stSearch_Node   fn 小的在靠前
	std::vector <stSearch_Node> close_search_node_pool;
	
	std::vector <bool> visited;

	int search_count;//搜索过程计数
	int expand_node_count;//扩展节点
public:
	CAgent(int agentid,stPoint init,stPoint goal, CGridMap* gridmap,CDistance* cdistance);
	~CAgent();
	/*向外扩张一次 扩张成功返回0 找到目标节点返回1 失败返回2*/
	int search_step();
	
	///启发式函数 曼哈顿距离
	int h(const stPoint& init, const stPoint& goal);
	///启发式函数 真实距离
	int h(const stPoint& init, const stPoint& goal, CGridMap* gridmap);
	
	std::vector <int> get_path();

	int get_agent_id();
	int get_expand_node_count();
};
inline
int CAgent::h(const stPoint& init, const stPoint& goal)
{
	int cost = 0;
	int xd = init.x - goal.x;
	int yd = init.y - goal.y;
	cost += (xd > 0) ? xd : -xd;
	cost += (yd > 0) ? yd : -yd;
	return cost;
}
inline
int CAgent::get_agent_id()
{
	return agentid;
}

inline int CAgent::get_expand_node_count()
{
	return expand_node_count;
}
