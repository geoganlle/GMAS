#include "GenerateMAS.h"

std::string GenerateMAS::generateAgentFileName()
{
	int fileindex = 0;
	std::stringstream ss;
	std::fstream _file;
	if (_mkdir("../mas"))std::cout << "\nmkdir failed: Folder \"mas\" already exists" << std::endl;//目录已存在
	do {
		if (_file.is_open())_file.close();
		ss.clear();
		_file.clear();
		string_mas_name.clear();
		ss << "../mas/" << int_dim_x << "x" << int_dim_y << "mas" << fileindex << ".txt";
		fileindex++;
		ss >> string_mas_name;
		_file.open(string_mas_name, std::ios::in);
	} while (_file);
	_file.close();
	return string_mas_name;
}

bool GenerateMAS::RandGenerateAgent()
{
	int* hashintmap = new int[(__int64)int_dim_x * (__int64)int_dim_y];
	try
	{
		for (int i = 0; i < (__int64)int_dim_x * (__int64)int_dim_y; i++) {
			hashintmap[i] = i;
		}
		std::default_random_engine random(static_cast<unsigned int>(time(NULL)));
		int agent_pos_int_number = (int_agent_number * 2);
		for (int i = 0; i < int_dim_x * int_dim_y && static_cast<int>(int_cached.size())< agent_pos_int_number; i++) {//等概率生成n个随机位置
			std::uniform_int_distribution<int> intdis(i, int_dim_x * int_dim_y - 1);
			int j = intdis(random);
			if (i >= 0 && j >= 0 &&
				i < (__int64)int_dim_x * (__int64)int_dim_y &&
				j < (__int64)int_dim_x * (__int64)int_dim_y &&
				gridmap->checkNodeInput(0, 0) &&
				int_dim_x != 0 && int_dim_y != 0
				) {//确保int_map已被初始化
				std::swap(hashintmap[i], hashintmap[j]);
				if(gridmap->visitNode(hashintmap[i]%int_dim_x, hashintmap[i]/int_dim_x))
				int_cached.push_back(hashintmap[i]);
			}
			else {
				//std::cout << "Log5" << std::endl;
				throw new std::exception("Array overflow/underflow error");
			}
		}
		std::cout << "rand number" << int_cached.size() << "/" << (__int64)int_dim_x * (__int64)int_dim_y << std::endl;
		//for (int i = 0; i < (__int64)int_dim_x * (__int64)int_dim_y; i++) {
		//	std::cout<<hashintmap[i]<<" ";
		//}
		delete[] hashintmap;
		return true;
	}
	catch (const std::exception & e)
	{
		//std::cout << "Log6" << std::endl;
		std::cerr << e.what() << std::endl;
		delete[] hashintmap;
		return false;
	}
};

void GenerateMAS::PrintConsole()
{
	std::cout << "GenerateMAS file name :" << string_mas_name<< std::endl;;
	for (auto it = int_cached.begin(); it != int_cached.end(); it++) {
		std::cout << (*it) << " ";
	}
	std::cout << "\n";
}

void GenerateMAS::WriteFile()
{
	if (!checkNodeInput(0, 0)) {
		std::cout << "checkNodeInput(0,0 failed)" << std::endl;
		return ;
	}
	std::cout << "Writing file:" << string_mas_name << std::endl;
	std::ofstream __file;
	__file.open(string_mas_name, std::ios::out | std::ios::trunc);
	if (!__file.is_open()) {
		std::cout << "file open failed" << std::endl;
		system("PAUSE");
		__file.close();
		return ;
	}
	__file << "# generate agent number" << int_cached.size()/2<<"\n";
	__file << "# init_point(x,y) goal_point(x,y)\n";
	__file <<gridmap->get_string_map_name()<<"\n";
	for (auto it = int_cached.begin(); it != int_cached.end(); it++) {
		__file << (*it)%int_dim_x << " " << (*it) / int_dim_x;
		if ((it - int_cached.begin())%2 == 1) {
			__file << "\n";
		}
		else {
			__file << " ";
		};
	}
	__file.close();
	std::cout << "Writing finished:" << string_mas_name << std::endl;
}

GenerateMAS::GenerateMAS(int agent_number_in, GenerateMap* gridmap_in)
	:int_agent_number(agent_number_in),gridmap(gridmap_in)
{
	int_dim_x = gridmap->getDimx();
	int_dim_y = gridmap->getDimy();
	string_mas_name = generate_file_name("mas", int_dim_x, int_dim_y);
}

GenerateMAS::~GenerateMAS()
{
	std::cout << "~GenerateMAS()" << std::endl;
	int_cached.clear();
}
