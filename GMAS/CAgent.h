#pragma once
#include "CGridMap.h"
#include "CBfs.h"
#include "CDistance.h"
#include<vector>
#include <map>
#include <unordered_set>
constexpr auto MAX_SEARCH_COUNT = 1000;

struct stSearch_Node {//����A*�������̵Ľṹ��
	stPoint location;//����
	int fn;
	int gn;
	int hn;
	int agentid;
	int dir_to_parent;//���ڵ�ķ������ڴ�Ŀ����������·��
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

	std::vector <stSearch_Node> search_node_pool;//�ֶ�ά�� stSearch_Node   fn С���ڿ�ǰ
	std::vector <stSearch_Node> close_search_node_pool;//����������Ľڵ㼯
	
	std::vector <bool> visited;//����������� 
	//TODO:�����Ż�ɾ�� ��search_node_pool��close_search_node_pool����
	int search_count;//�������̼���
	//TODO:�����Ż�ɾ�� ʵ���Ͼ���close_search_noed_pool��Ԫ�صĸ���
	int expand_node_count;//��չ�ڵ����
	//TODO:�����Ż�ɾ�� ʵ���Ͼ���search_node_pool��close_search_noed_pool��Ԫ�ص�����
public:
	std::vector <stPoint> get_Next_expand_node();//��ȡ������
	CAgent(int agentid, stPoint init, stPoint goal, CGridMap* gridmap, CDistance* cdistance);
	~CAgent();
	/*��������һ�� ���ųɹ�0 �ҵ�Ŀ��ڵ㷵��1 ��չ�����2 Ŀ�ĵ㲻�ɴ�3*/
	int search_step();
	int search_step(const std::vector<int> & ignoreNodeVector);
	//TODO:���Ż� ��search_step�ϲ�

	///�ƶ�һ�� �����ƶ��������
	///stPoint move_step(std::vector <stPoint> ignorePoint_vector);
	
	///�����پ���
	int ManhattanDistance(const stPoint& init, const stPoint& goal);
	///�Զ����ͼ����
	int CustomMapDistance(const stPoint& init, const stPoint& goal, const stPoint & map_DIM);
	///BFS��ʵ����
	int BFSDistance(const stPoint& init, const stPoint& goal, CGridMap* gridmap);
	//����ʽ����
	int h(const stPoint& init, const stPoint& goal, CGridMap* gridmap);
	std::vector <int> get_path();//��ȡ·��
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
