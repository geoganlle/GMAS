#include "CGridMap.h"
#include <vector>
#include <string>

void CGridMap::printGridMap()
{
	std::cout<<"GridMap Print:"<<std::endl;
	for (int i = 0; i < dimY_int; i++) {
		for (int j = 0; j < dimX_int; j++) {
			std::cout << ((map_boolpp[i][j]) ? 1 : 0);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/*检测周围8个点是否可通行*/
bool* CGridMap::getNeighbor(const stPoint& pos) const
{
	int y = pos.y;
	int x = pos.x;

	//输入点越界则直接返回
	if (x < 0 || x >= dimX_int || y < 0 || y >= dimY_int)
		return NULL;

	bool* neighbor = new bool[DIM];
	/*	WN			N		EN
		y-1,x-1		y-1,x	y-1,x+1
	W	y,x-1		y,x		y,x+1		E
		y+1,x-1		y+1,x	y+1,x+1
		WS			S		ES
	*/
	neighbor[EAST] = x + 1 < dimX_int && map_boolpp[y][x+1];
	neighbor[SOUTH] = y + 1 < dimY_int && map_boolpp[y+1][x];
	neighbor[WEST] = x - 1 >= 0 && map_boolpp[y][x-1];
	neighbor[NORTH] = y - 1 >= 0 && map_boolpp[y - 1][x];

	neighbor[EN] = y - 1 >= 0 && x + 1 < dimX_int && map_boolpp[y - 1][x + 1];
	neighbor[ES] = y + 1 < dimY_int && x + 1 < dimX_int && map_boolpp[y + 1][x + 1];
	neighbor[WS] = y + 1 < dimY_int && x - 1 >= 0 && map_boolpp[y + 1][x - 1];
	neighbor[WN] = y - 1 >= 0 && x - 1 >= 0 && map_boolpp[y - 1][x - 1];

	return neighbor;
}

CGridMap::CGridMap(std::string pathname)
{
	std::string	line_string;
	std::ifstream	file(pathname);
	std::vector<std::string> gridmap_line_vector;

	if (file.is_open()) {
		while (std::getline(file, line_string) && line_string.size()) {//读一行行长度不为0
			gridmap_line_vector.push_back(line_string);
		}
		file.close();
	}
	else {
		std::cout << "ERROR: Could not open file " + pathname << std::endl;;
	}
	dimY_int = static_cast<int> (gridmap_line_vector.size());
	dimX_int = static_cast<int> (gridmap_line_vector.at(0).size());

	map_boolpp = new bool* [dimY_int];
	for (int i = 0; i < dimY_int; i++) {
		map_boolpp[i] = new bool[dimX_int];
		for (int j = 0; j < dimX_int; j++) {
			// true 1 false 0
			map_boolpp[i][j] = (gridmap_line_vector[i][j] == '1');
		}
	}
	//printGridMap();
	std::cout << "dimX = " << dimX_int << " dimY = " << dimY_int <<std::endl;
}
/*
CGridMap::CGridMap(int dimX, int dimY, stPoint** blocklist, int listlen)
{
	dimX_int = dimX;
	dimY_int = dimY;
	stPoint** endPoint = blocklist + listlen;
	map_boolpp = new bool* [dimY];

	// true 1 false 0
	for (int i = 0; i < dimY; i++) {
		map_boolpp[i] = new bool[dimX];
		for (int j = 0; j < dimX; j++) {
			map_boolpp[i][j] = false; 
			if (blocklist && **blocklist==stPoint(i,j))//判断有没有障碍物
				blocklist = (blocklist + 1 == endPoint) ? 0 : blocklist + 1;//判断是否是最后一个障碍物
			else
				map_boolpp[i][j] = true;
		}
	}
}
*/


CGridMap::~CGridMap()
{
	//std::cout<<"Class CGridMap has been deconstructed"<<std::endl;
	for (int i = 0; i < dimY_int; i++) {
		delete[] map_boolpp[i];
	}
	delete[] map_boolpp;
}
