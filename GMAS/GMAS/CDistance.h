/*
program file No.3
配合CBfs.h优先遍历计算点之间的距离
这个距离可以理解为广度优先遍历的深度
用于A*算法中f(n)=g(n)+h(n)的h(n)的计算

单例模式

Written by Geoganlle Goo
**/
#pragma once
#include "CBfs.h"
#include "CGridMap.h"
#include <direct.h>

class CDistance
{
	CGridMap* gridmap_CGridMap;
	int** table_intpp;//任意两点间的距离表

	void populate();//初始化table_intpp 用广度优先遍历的方式
	void search(stPoint& o, stPoint& d);

public:
	int getDistance(const stPoint& init, const stPoint& goal);
	void setDistance(const stPoint& init, const stPoint& goal,const int distance);

	CDistance(CGridMap* gridmap, bool populate = false);
	~CDistance();
	void printDistanceTable();	//输出table_intpp中的值,仅用于调试输出

};

inline
int CDistance::getDistance(const stPoint& init, const stPoint& goal)
{
	int dimX = gridmap_CGridMap->getDim().x;
	int dimY = gridmap_CGridMap->getDim().y;
	return table_intpp[init.y * dimX + init.x][goal.y * dimX + goal.x];
}

inline void CDistance::setDistance(const stPoint& init, const stPoint& goal, const int distance)
{
	int dimX = gridmap_CGridMap->getDim().x;
	int dimY = gridmap_CGridMap->getDim().y;
	if (table_intpp) { 
		table_intpp[init.y * dimX + init.x][goal.y * dimX + goal.x] = distance; 
		table_intpp[goal.y * dimX + goal.x][init.y * dimX + init.x] = distance;//无向图
	}
}
