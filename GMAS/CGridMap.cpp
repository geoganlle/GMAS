#include "CGridMap.h"
#include <vector>
#include <string>

void CGridMap::printGridMap()
{
	std::cout<<"GridMap Print:"<<std::endl;
	for (int i = 0; i < dimY_int; i++) {
		for (int j = 0; j < dimX_int; j++) {
			std::cout << ((map_boolpp[i][j]) ? 1 : 0)<<" ";
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

std::vector<int> CGridMap::get_neighbor(const int& point_hash)
{
	std::vector<int> neighbor_vector;
	stPoint pos = unhash(point_hash);
	bool* neighbor_bp = getNeighbor(pos);
	for (int i=0;i<DIM;i++)
	{
		if (neighbor_bp[i] == 1)neighbor_vector.push_back(hashpt(dir_move_stPoint(pos,i)));
	}
	delete [] neighbor_bp;
	return neighbor_vector;
}

std::vector<int> CGridMap::get_gorge(const int& point_hash)
{
	std::vector<int> gorge_vector;
	gorge_vector.push_back(point_hash);
	std::vector<int> expand_queue;
	expand_queue.push_back(point_hash);
	while (!expand_queue.empty()) {
		int cur_point=expand_queue.back();
		std::vector<int> neighbor = get_neighbor(cur_point);
		expand_queue.pop_back();
		if (neighbor.size() != 2) {
			continue;
		}
		auto find_cur_point = std::find(gorge_vector.begin(), gorge_vector.end(), cur_point);
		auto find_first_neighbor = std::find(gorge_vector.begin(),gorge_vector.end(),neighbor[0]);
		auto find_second_neighbor = std::find(gorge_vector.begin(), gorge_vector.end(), neighbor[1]);
		if (find_first_neighbor == gorge_vector.end()&& find_second_neighbor == gorge_vector.end()) {
			if (find_cur_point == gorge_vector.end()) {
			continue;
			}
			gorge_vector.insert(find_cur_point, neighbor[0]);
			find_cur_point = std::find(gorge_vector.begin(), gorge_vector.end(), cur_point);
			gorge_vector.insert((find_cur_point + 1), neighbor[1]);
			expand_queue.push_back(neighbor[0]);
			expand_queue.push_back(neighbor[1]);
			continue;
		}
		if (find_first_neighbor == gorge_vector.end()) {
			if (1 == find_second_neighbor - find_cur_point)
			{
				gorge_vector.insert(find_cur_point, neighbor[0]);
			}
			else if (1 == find_cur_point- find_second_neighbor)
			{
				gorge_vector.insert(find_cur_point+1, neighbor[0]);
			}
			else {
				std::cout<<"ERRO:CGridMap::get_gorge insert first_neighbor"<<std::endl;
				return gorge_vector;
			}
			expand_queue.push_back(neighbor[0]);
			continue;
		}
		if (find_second_neighbor == gorge_vector.end()) {
			if (1 == find_first_neighbor - find_cur_point)
			{
				gorge_vector.insert(find_cur_point, neighbor[1]);
			}
			else if (1 == find_cur_point - find_first_neighbor)
			{
				gorge_vector.insert(find_cur_point + 1, neighbor[1]);
			}
			else {
				std::cout << "ERRO:CGridMap::get_gorge insert second_neighbor" << std::endl;
				return gorge_vector;
			}
			expand_queue.push_back(neighbor[1]);
			continue;
		}
	};
	return gorge_vector;
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
	//std::cout << "dimX = " << dimX_int << " dimY = " << dimY_int <<std::endl;
}

CGridMap::~CGridMap()
{
	//std::cout<<"Class CGridMap has been deconstructed"<<std::endl;
	for (int i = 0; i < dimY_int; i++) {
		delete[] map_boolpp[i];
	}
	delete[] map_boolpp;
}
