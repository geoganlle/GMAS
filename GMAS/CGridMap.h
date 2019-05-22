/*
program file No.1

��Ҫ����:
stPoint �ṹ�� �洢��άƽ��ĵ�
eDirection ö�� �趨8������ ���뷽���йصķ���
cGridMap �� ��������ͼ��ر����ͷ���
	
����˵����
	1.��ά���顰map_intpp����ʽ��
		x-> x����
	  y	0123456789
	  |	1234567898
	  V	2345678987
		3456789876
	  y	4567898765
	 ��	5678987654
	 ��	6789876543

	eg:map_intpp[3][2];ָy����ȡ���ĸ�λ�ã�x����ȡ������λ��

	2.�����ϱ����������Ҷ��������������Ұ�����������ʽ�涨
	WN					N ��				EN
			|y-1,x-1 |	y-1,x |	y-1,x+1 |
	W ��	|y,x-1	 |	y,x	  |	y,x+1	|	E ��
			|y+1,x-1 |	y+1,x | y+1,x+1 |
	WS					S ��				ES

Written by Geoganlle Goo
**/
#pragma once
#include<iostream>
#include<fstream>
constexpr auto DIM = 8;//8������;

struct stPoint {
	int x;
	int y;
	stPoint(int inputx = 0 , int inputy = 0 ) : x(inputx) , y(inputy) {};
	void operator()(const stPoint& cp){
		x = cp.x;
		y = cp.y;
	};
	bool operator==(const stPoint& point_input) { 
		return this->x == point_input.x && this->y == point_input.y; 
	};
};

enum eDirection{EAST,SOUTH,WEST,NORTH,EN,ES,WS,WN,WAIT};//9������

/*������*/
inline
int dir_reverse(int dir) {
	switch (dir) {
	case EAST:
		return WEST;
	case SOUTH:
		return NORTH;
	case WEST:
		return EAST;
	case NORTH:
		return SOUTH;
	case EN:
		return WS;
	case ES:
		return WN;
	case WS:
		return EN;
	case WN:
		return ES;
	default:
		return dir;
	}
}

/*�����ķ���*/
inline
int dir_get(stPoint* from, stPoint* to) {
	int dx, dy, diff;
	if (!(from && to)) return -1;	// Error
	dx = to->x - from->x;
	dy = to->y - from->y;
	diff = 3 * dy + dx;
	/*
		dx = | -1	0	1 |	3 * dy = | -3  -3  -3 |
			 | -1	0	1 |			 |  0	0	0 |
			 | -1	0	1 |		     |  3	3	3 |
		3 * dy + dx = | -4	-3	-2 |	WN	N	EN
					  | -1	 0	 1 |	W		E
					  |  2	 3	 4 |	WS	S	ES
	**/
	switch (diff) {
	case 4:
		return ES;
	case 3:
		return SOUTH;
	case 2:
		return WS;
	case 1:
		return EAST;
	case 0:
		return WAIT;
	case -1:
		return WEST;
	case -2:
		return EN;
	case -3:
		return NORTH;
	case -4:
		return WN;
	default:
		return -1;
	}

}

/*�õ�ĳһ����ĵ� ע��:���ܷ��ص�ͼ��ĵ�*/
inline
stPoint dir_move_stPoint(const stPoint from, int dir) {

	/*						��
			y - 1, x - 1	y - 1, x	y - 1, x + 1
		��	y, x - 1		y, x		y, x + 1		��
			y + 1, x - 1	y + 1, x	y + 1, x + 1
							��
	**/
	
	stPoint point(from.x, from.y);
	switch (dir) {
	case EAST:
		point.x++; 
		break;
	case SOUTH:
		point.y++; 
		break;
	case WEST:
		point.x--; 
		break;
	case NORTH:
		point.y--; 
		break;
	case EN:
		point.x++;
		point.y--;
		break;
	case ES:
		point.x++;
		point.y++;
		break;
	case WS:
		point.x--;
		point.y++;
		break;
	case WN:
		point.x--;
		point.y--;
		break;
	default:
		return point;
	}
	return point;
}

/*����ת��Ϊ�ַ���*/
inline
std::string dir_to_string(int dir) {
	switch (dir) {
	case NORTH:
		return "North";
	case SOUTH:
		return "South";
	case EAST:
		return "East";
	case WEST:
		return "West";
	case EN:
		return "NorthEast";
	case WN:
		return "NorthwWest";
	case ES:
		return "SouthEast";
	case WS:
		return "SouthWest";
	case WAIT:
		return "Wait";
	default:
		return "";
	}
}

class CGridMap
{
private:
	bool** map_boolpp;//1(true)���ϰ��� 0(false)���ϰ���
	int dimY_int;//��ͼ��y��ߴ�
	int dimX_int;//��ͼ��x��ߴ�
public:
	void printGridMap();//�ڿ���̨�����ͼ��Ϣ

	bool* getNeighbor(const stPoint& pos) const;//���pos��Χ8��λ���Ƿ��ͨ��
	bool passable(const stPoint& pos)const;//���posλ���Ƿ��е�
	stPoint getDim();//�õ���ͼ�ߴ�

	int hashpt(const stPoint& p);//����ͼ�е�һ������ӳ�䵽��һλ������±�
	stPoint unhash(int hash);//��һ�������±�ӳ��ɵ�ͼ�ϵ�

	CGridMap(std::string pathname);//���ļ��ж�ȡ��ͼ
	//CGridMap(int dimX, int dimY, stPoint** blocklist, int listlen);//����һ���ϰ���㴴����ͼ
	~CGridMap();
	
};
//�������� �Ż�����Ч��
inline bool CGridMap::passable(const stPoint& pos) const
{
	return (pos.x >= 0 && pos.x < dimX_int &&
		pos.y >= 0 && pos.y < dimY_int
		&& map_boolpp[pos.y][pos.x]);
}
inline
stPoint CGridMap::getDim()
{
	return stPoint(dimX_int, dimY_int);
}
inline
int CGridMap::hashpt(const stPoint & p)
{
	return (p.y * dimX_int + p.x);
}
inline
stPoint CGridMap::unhash(int hash)
{
	return stPoint( hash % dimX_int ,hash / dimX_int );
	//x,y
}