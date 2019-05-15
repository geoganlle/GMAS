#include "CDistance.h"

void CDistance::populate()
{
	int dimX = gridmap_CGridMap->getDim().x;
	int dimY = gridmap_CGridMap->getDim().y;
	for (int i = 0; i < dimX; i++) {
		for (int j = 0; j < dimY; j++) {
			stPoint orig(i, j);
			for (int k = 0; k < dimX; k++) {
				for (int l = 0; l < dimY; l++) {
					stPoint dest(k, l);
					search(orig, dest);
				}
			}
		}
	}
}

void CDistance::search(stPoint& o, stPoint& d)
{
	int dimX = gridmap_CGridMap->getDim().x;
	int dimY = gridmap_CGridMap->getDim().y;
	CBfs* bfs=new CBfs(&o, &d, this->gridmap_CGridMap);
	if(gridmap_CGridMap->hashpt(&o)< (dimX * dimY)&&gridmap_CGridMap->hashpt(&d)<(dimX * dimY))
	table_intpp[gridmap_CGridMap->hashpt(&o)][gridmap_CGridMap->hashpt(&d)] = (*bfs).get_soln_cost_int();
	bfs ->~CBfs();
}

CDistance::CDistance(CGridMap* gridmap,bool do_populate):gridmap_CGridMap(gridmap)
{
	stPoint dim = gridmap_CGridMap->getDim();
	int len = dim.x * dim.y;
	table_intpp = new int* [len];
	for (int i = 0; i < len; i++) {
		table_intpp[i] = new int[len];
	}
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			table_intpp[i][j] = INT_MAX;
		}
	}
	if (do_populate)this->populate();
}

CDistance::~CDistance()
{
	int dimX = gridmap_CGridMap->getDim().x;
	int dimY = gridmap_CGridMap->getDim().y;
	for (int i = 0; i < dimX * dimY; i++)
		delete[] table_intpp[i];
	delete[] table_intpp;
}

void CDistance::printDistanceTable()
{
	int n = gridmap_CGridMap->getDim().x * gridmap_CGridMap->getDim().y;
	std::ofstream __file;
	if (_mkdir("../distance"))std::cout << "mkdir failed: Folder \"distance\" already exists" << std::endl;//Ä¿Â¼ÒÑ´æÔÚ
	__file.open("../distance/table.txt", std::ios::out | std::ios::trunc);
	if (!__file.is_open()) {
		std::cout << "file open failed" << std::endl;
		__file.close();
		return;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			__file << table_intpp[i][j] << "\t";
		}
		__file << std::endl;
	}
	__file.close();
	std::cout << "file written in /distance/table.txt finish" << std::endl;
}
