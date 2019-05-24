#pragma once
#include <string>
#include <direct.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "GenerateMAS.h"
class GlobalFunction
{
public:
	GlobalFunction();
	~GlobalFunction();
};
std::string generate_file_name(std::string path_name,int dimx,int dimy);

void  create_mas_task(int mas_number);//创建多个任务