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
	int int_dim_x ;
	int int_dim_y;
	GenerateMap* gridmap;
	std::vector <int> int_cached;

	std::string string_mas_name;//д���ļ�������
	std::string generateAgentFileName();//�����ļ���
public:
	bool RandGenerateAgent();
	bool checkNodeInput(const int& x, const int& y);

	void PrintConsole();
	void WriteFile();

	GenerateMAS(int agent_number,GenerateMap* gridmap);
	~GenerateMAS();
};

inline bool GenerateMAS::checkNodeInput(const int& x, const int& y)
{
	if (x<0 || y<0 || x>int_dim_x || y>int_dim_y || int_cached.empty()) return false;
	return true;
}

