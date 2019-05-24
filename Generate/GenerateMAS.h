#pragma once
#include<iostream>
#include<string>
#include<random>  
#include<time.h>  
#include<sstream>
#include<exception>
#include<fstream>
#include<direct.h>
#include "GenerateMap.h"
class GenerateMAS
{
	int int_agent_number;
	int int_dim_x;
	int int_dim_y;
	GenerateMap* gridmap;
	std::vector <int> int_cached;

	std::string string_mas_name;//写入文件的名字
	std::string generateAgentFileName();//生成文件名
public:
	std::string get_mas_name();
	bool RandGenerateAgent();
	bool checkNodeInput(const int& x, const int& y);

	void PrintConsole();
	void WriteFile();

	GenerateMAS(int agent_number,GenerateMap* gridmap);
	~GenerateMAS();
};
inline
std::string GenerateMAS::get_mas_name()
{
	return this->string_mas_name;
}

inline bool GenerateMAS::checkNodeInput(const int& x, const int& y)
{
	if (x<0 || y<0 || x>int_dim_x || y>int_dim_y || int_cached.empty()) return false;
	return true;
}

