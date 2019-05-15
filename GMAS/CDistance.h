/*
program file No.3
���CBfs.h���ȱ��������֮��ľ���
�������������Ϊ������ȱ��������
����A*�㷨��f(n)=g(n)+h(n)��h(n)�ļ���

����ģʽ

Written by Geoganlle Goo
**/
#pragma once
#include "CBfs.h"
#include "CGridMap.h"
#include <direct.h>

class CDistance
{
	CGridMap* gridmap_CGridMap;
	int** table_intpp;//���������ľ����

	void populate();//��ʼ��table_intpp �ù�����ȱ����ķ�ʽ
	void search(stPoint& o, stPoint& d);

public:
	int getDistance(const stPoint& init, const stPoint& goal);
	void setDistance(const stPoint& init, const stPoint& goal,const int distance);

	CDistance(CGridMap* gridmap, bool populate = false);
	~CDistance();
	void printDistanceTable();	//���table_intpp�е�ֵ,�����ڵ������

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
		table_intpp[goal.y * dimX + goal.x][init.y * dimX + init.x] = distance;//����ͼ
	}
}
