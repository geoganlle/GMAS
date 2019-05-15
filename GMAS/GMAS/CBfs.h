/*
program file No.2
�����������
�����ͼ�������ľ���
��Ҫ����ȷ��·���Ƿ����
Written by Geoganlle Goo
**/
#pragma once
#include <iostream>
#include <queue>
#include "CGridMap.h"

struct stPointBFS {
	stPoint p_stPoint;
	int dir_int;//�򸸽ڵ㷽��
	int depth_int;//���
	stPointBFS(stPoint c, int dir, int depth) : p_stPoint(c), dir_int(dir), depth_int(depth) { };
};

class CBfs
{
	int soln_cost_int;//����
	CGridMap* gridmap_CGridMapp;//��ͼ
	stPoint dim_stPoint;//��ͼ�ߴ�
	stPoint* orig_stPoint;//���
	stPoint* dest_stPoint;//�յ�

	bool* visited_boolp;//���ڹ�����ȱ��������飬����ѷ��ʹ��ĵ�
	int visited_length_int;//visited_boolp����ĳ���

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
