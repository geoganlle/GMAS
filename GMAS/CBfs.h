/*
program file No.2
广度优先搜索
计算地图中两点间的距离
主要用于确认路径是否存在
Written by Geoganlle Goo
**/
#pragma once
#include <iostream>
#include <queue>
#include "CGridMap.h"

struct stPointBFS {
	stPoint p_stPoint;
	int dir_int;//向父节点方向
	int depth_int;//深度
	stPointBFS(stPoint c, int dir, int depth) : p_stPoint(c), dir_int(dir), depth_int(depth) { };
};

class CBfs
{
	int soln_cost_int;//消耗
	CGridMap* gridmap_CGridMapp;//地图
	stPoint dim_stPoint;//地图尺寸
	stPoint* orig_stPoint;//起点
	stPoint* dest_stPoint;//终点

	bool* visited_boolp;//用于广度优先遍历的数组，标记已访问过的点
	int visited_length_int;//visited_boolp数组的长度

public:
	CBfs(stPoint* o,stPoint* d,CGridMap* g);
	~CBfs();

	void search();
	int get_soln_cost_int();
};

inline
int CBfs::get_soln_cost_int()
{
	return soln_cost_int;
}
