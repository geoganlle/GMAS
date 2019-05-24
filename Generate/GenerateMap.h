#pragma once
#include<iostream>
#include<string>
#include<random>  
#include<time.h>  
#include<sstream>
#include<exception>
#include<fstream>
#include<direct.h>

std::string generate_file_name(std::string path_name = "", int dimx = 0, int dimy = 0);

class GenerateMap
{
private:
	int int_dim_x;//地图尺寸
	int int_dim_y;
	int** int_map;//地图内容 0障碍物 1可通行 -1待扩展
	std::string string_map_name;//写入文件的名字

	std::string generateMapName();//生成文件名
public:
	/*随机生成地图
	maptype 障碍物类型 0:点 1:图形 2:迷宫 
	density: 可通行率 既无障碍物点的比率*/
	bool RandGenerateMap(const int& maptype= 0, const double& density = 0.4);
public:
	int getDimx();
	int getDimy();
	GenerateMap();
	GenerateMap(const int& dimx, const int& dimy);
	~GenerateMap();
	bool WriteFile();//写入文件
	bool PrintConsole();//控制台输出

	inline bool checkNodeInput(const int& x,const int& y);//检查坐标是否越界
	inline int visitNode(const int& x, const int& y);
	inline int visitDimX();
	inline int visitDimY();
	inline std::string get_string_map_name();
};

inline
int GenerateMap::getDimx()
{
	return int_dim_x;
};

inline
int GenerateMap::getDimy()
{
	return int_dim_y;
};

inline bool GenerateMap::checkNodeInput(const int& x, const int& y)
{
	if (x<0 || y<0 || x>int_dim_x || y>int_dim_y || int_map == NULL) return false;
	return true;
}

inline int GenerateMap::visitNode(const int& x, const int& y)
{
	if (!checkNodeInput(x, y))return -1;
	return int_map[x][y];
}

inline int GenerateMap::visitDimX()
{
	return int_dim_x;
}

inline int GenerateMap::visitDimY()
{
	return int_dim_y;
}

inline std::string GenerateMap::get_string_map_name()
{
	return string_map_name;
}
