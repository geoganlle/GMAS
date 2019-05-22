/*
program file No.1

主要内容:
stPoint 结构体 存储二维平面的点
eDirection 枚举 设定8个方向 及与方向有关的方法
cGridMap 类 处理环境地图相关变量和方法
	
基本说明：
	1.二维数组“map_intpp”格式：
		x-> x方向
	  y	0123456789
	  |	1234567898
	  V	2345678987
		3456789876
	  y	4567898765
	 方	5678987654
	 向	6789876543

	eg:map_intpp[3][2];指y方向取第四个位置，x方向取第三个位置

	2.方向：上北下南左西右东，其中上下左右按下面的数组格式规定
	WN					N 北				EN
			|y-1,x-1 |	y-1,x |	y-1,x+1 |
	W 西	|y,x-1	 |	y,x	  |	y,x+1	|	E 东
			|y+1,x-1 |	y+1,x | y+1,x+1 |
	WS					S 南				ES

Written by Geoganlle Goo
**/
#pragma once
#include<iostream>
#include<fstream>
constexpr auto DIM = 8;//8个方向;

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

enum eDirection{EAST,SOUTH,WEST,NORTH,EN,ES,WS,WN,WAIT};//9个方向

/*反方向*/
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

/*两点间的方向*/
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

/*得到某一方向的点 注意:可能返回地图外的点*/
inline
stPoint dir_move_stPoint(const stPoint from, int dir) {

	/*						北
			y - 1, x - 1	y - 1, x	y - 1, x + 1
		西	y, x - 1		y, x		y, x + 1		东
			y + 1, x - 1	y + 1, x	y + 1, x + 1
							南
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

/*方向转化为字符串*/
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
	bool** map_boolpp;//1(true)无障碍物 0(false)有障碍物
	int dimY_int;//地图的y轴尺寸
	int dimX_int;//地图的x轴尺寸
public:
	void printGridMap();//在控制台输出地图信息

	bool* getNeighbor(const stPoint& pos) const;//检测pos周围8个位置是否可通行
	bool passable(const stPoint& pos)const;//检测pos位置是否有点
	stPoint getDim();//得到地图尺寸

	int hashpt(const stPoint& p);//将地图中的一个坐标映射到成一位数组的下标
	stPoint unhash(int hash);//将一个数组下标映射成地图上的

	CGridMap(std::string pathname);//从文件中读取地图
	//CGridMap(int dimX, int dimY, stPoint** blocklist, int listlen);//根据一组障碍物点创建地图
	~CGridMap();
	
};
//内联函数 优化函数效率
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