#pragma once
#include "CGridMap.h"
#include "CBfs.h"
#include "CDistance.h"
#include<vector>
#include <map>
#include <unordered_set>
constexpr auto MAX_SEARCH_COUNT = 1000;

struct stSearch_Node {//用于A*搜索过程的结构体
	stPoint location;//坐标
	int fn;
	int gn;
	int hn;
	int agentid;
	int dir_to_parent;//父节点的方向，用于从目标点回溯完整路径
	stSearch_Node(stPoint location_i= stPoint(),int agentid_i=0, int gn_i=0, int hn_i=0,int dir_to_parent_i=DIM)
		:location(location_i),agentid(agentid_i), gn(gn_i), hn(hn_i), dir_to_parent(dir_to_parent_i){ fn = gn + hn; };
};

class CAgent
{
	int agentid;
	stPoint init;
	stPoint goal;
	std::vector <int> path_hash;
	CGridMap* gridmap;
	CDistance* cdistance;

	std::vector <stSearch_Node> search_node_pool;//手动维护 stSearch_Node   fn 小的在靠前
	std::vector <stSearch_Node> close_search_node_pool;//已完成搜索的节点集
	
	std::vector <bool> visited;//辅助标记数组 
	//TODO:可以优化删除 用search_node_pool和close_search_node_pool代替
	int search_count;//搜索过程计数
	//TODO:可以优化删除 实际上就是close_search_noed_pool中元素的个数
	int expand_node_count;//扩展节点计数
	//TODO:可以优化删除 实际上就是search_node_pool和close_search_noed_pool中元素的总数
public:
	std::vector <stPoint> get_Next_expand_node();//获取接下来
	CAgent(int agentid, stPoint init, stPoint goal, CGridMap* gridmap, CDistance* cdistance);
	~CAgent();
	/*向外扩张一次 扩张成功0 找到目标节点返回1 扩展点过多2 目的点不可达3*/
	int search_step();
	int search_step(const std::vector<int> & ignoreNodeVector);
	//TODO:可优化 与search_step合并

	///移动一次 返回移动后的坐标
	///stPoint move_step(std::vector <stPoint> ignorePoint_vector);
	
	///曼哈顿距离
	int ManhattanDistance(const stPoint& init, const stPoint& goal);
	///自定义地图距离
	int CustomMapDistance(const stPoint& init, const stPoint& goal, const stPoint & map_DIM);
	///BFS真实距离
	int BFSDistance(const stPoint& init, const stPoint& goal, CGridMap* gridmap);
	//启发式函数
	int h(const stPoint& init, const stPoint& goal, CGridMap* gridmap);
	std::vector <int> get_path();//获取路径
	int get_agent_id();
	int get_expand_node_count();
	inline const stPoint get_initPoint();
	inline const stPoint get_goalPoint();
	inline void set_goalPoint(const stPoint&);
};
inline
int CAgent::ManhattanDistance(const stPoint& init, const stPoint& goal)
{
	int xd = abs(init.x - goal.x);
	int yd = abs(init.y - goal.y);
	return xd + yd;
}
inline int CAgent::CustomMapDistance(const stPoint& init, const stPoint& goal, const stPoint& map_DIM)
{
	int xd = abs(init.x - goal.x);
	int yd = abs(init.y - goal.y);
	return xd + yd - std::min(xd, yd);
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

inline const stPoint CAgent::get_initPoint()
{
	return init;
}

inline const stPoint CAgent::get_goalPoint()
{
	return goal;
}

inline void CAgent::set_goalPoint(const stPoint& goalPoint)
{
	goal = goalPoint;
}
