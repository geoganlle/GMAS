#include "GenerateMap.h"

std::string GenerateMap::generateMapName()
{
	int fileindex = 0;
	std::stringstream ss;
	std::fstream _file;
	if (_mkdir("../map"))std::cout << "mkdir failed: Folder \"map\" already exists" << std::endl;//目录已存在
	do{
		if(_file.is_open())_file.close();
		ss.clear();
		_file.clear();
		string_map_name.clear();
		ss <<"../map/"<<int_dim_x << "x" << int_dim_y << "map" << fileindex<<".txt";
		fileindex++;
		ss >> string_map_name;
		_file.open(string_map_name, std::ios::in);
	} while (_file);
	_file.close();
	return string_map_name;
}

bool GenerateMap::RandGenerateMap(const int& maptype, const double& density)
{

	int* hashintmap = new int[(__int64)int_dim_x * (__int64)int_dim_y];
	try
	{
		for (int i = 0; i < (__int64)int_dim_x * (__int64)int_dim_y; i++) {
			hashintmap[i] = i;
		}
		std::default_random_engine random(static_cast<unsigned int>(time(NULL)));
		for (int i = 0;i<int_dim_x * int_dim_y && i < ((__int64)int_dim_x * (__int64)int_dim_y)* density ;i++) {//等概率生成n个随机位置
			std::uniform_int_distribution<int> intdis(i, int_dim_x * int_dim_y - 1);
			int j = intdis(random);
			if (i >= 0 && j >= 0 && 
				i < (__int64)int_dim_x * (__int64)int_dim_y && 
				j < (__int64)int_dim_x * (__int64)int_dim_y &&
				checkNodeInput(0, 0) &&
				int_dim_x != 0 && int_dim_y != 0
				) {//确保int_map已被初始化
				std::swap(hashintmap[i], hashintmap[j]);
				this->int_map[hashintmap[i] / int_dim_x ][hashintmap[i] % int_dim_x] = 1;
			}else {
				throw new std::exception("Array overflow/underflow error");
				return false;
			}
		}
		std::cout <<"rand number"<< std::floor(((__int64)int_dim_x * (__int64)int_dim_y) * density )<<"/"<< (__int64)int_dim_x * (__int64)int_dim_y << std::endl;
		delete[] hashintmap;
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		delete[] hashintmap;
		return false;
	}
}


GenerateMap::GenerateMap()
{
	std::default_random_engine random(static_cast<unsigned int>(time(NULL)));
	std::uniform_int_distribution<int> intdis(10, 20);
	//std::uniform_real_distribution<double> dis2(0.0, 1.0);
	
	int_dim_x = intdis(random);
	int_dim_y = intdis(random);
	if (int_map != NULL) {
		for (int i = 0; i < int_dim_y; i++)
		{
			delete[] int_map[i];
		}
		delete[] int_map;
		int_map = NULL;
	}
	int_map = new int* [int_dim_y];
	for (int i = 0; i < int_dim_y; i++)
	{
		int_map[i] = new int[int_dim_x];
	}
	for (int row = 0; row < int_dim_y; row++) {
		for (int col = 0; col < int_dim_x; col++) {
			int_map[row][col] = 0;
		}
	}
	this->string_map_name = generateMapName();
}

GenerateMap::GenerateMap(const int& dimx, const int& dimy)
{
	int_dim_x = dimx;
	int_dim_y = dimy;
	if (int_map != NULL) {
		for (int i = 0; i < int_dim_y; i++)
		{
			delete[] int_map[i];
		}
		delete[] int_map;
		int_map = NULL;
	}
	int_map = new int* [int_dim_y];
	for (int i = 0; i < int_dim_y; i++)
	{
		int_map [i] = new int[int_dim_x];
	}
	for (int row = 0; row < int_dim_y; row++) {
		for (int col = 0; col < int_dim_x; col++) {
			int_map[row][col] = 0;
		}
	}
	this->string_map_name = generateMapName();
}


GenerateMap::~GenerateMap()
{
	for (int i = 0; i < int_dim_y; i++)
	{
		delete [] int_map[i];
	}
	delete [] int_map;
	int_map = NULL;
	std::cout << "~GenerateMap()" << std::endl;;
}

bool GenerateMap::WriteFile()
{
	if (!checkNodeInput(0, 0)) {
		std::cout << "checkNodeInput(0,0 failed)" << std::endl;
		return false;
	}
	std::cout <<"Writing file:"<< string_map_name << std::endl;
	std::ofstream __file;
	__file.open(string_map_name, std::ios::out|std::ios::trunc);
	if (!__file.is_open()) {
		std::cout << "file open failed" << std::endl;
		system("PAUSE");
		__file.close();
		return false;
	}
	for (int row = 0; row < int_dim_y; row++) {
		for (int col = 0; col < int_dim_x; col++) {
			__file << int_map[row][col];
		}
		__file << std::endl;
	}
	__file.close();
	std::cout << "Writing finished:" << string_map_name << std::endl;
	return true;
}

bool GenerateMap::PrintConsole()
{
	std::cout << "====================" << std::endl;
	std::cout << string_map_name << std::endl;
	std::cout << "--------------------" << std::endl;
	if (!checkNodeInput(0, 0)) { 
		//std::cout << "地图未生成" << std::endl;
		std::cout << "===================" << std::endl;
		return false; 
	}
	for (int row = 0; row < int_dim_y; row++) {
		for (int col = 0; col < int_dim_x; col++) {
			std::cout << int_map[row][col];
		}
		std::cout << std::endl;
	}
	std::cout << "===================" << std::endl;
	return true;
}

