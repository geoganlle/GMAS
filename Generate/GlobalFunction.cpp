#include "GlobalFunction.h"

GlobalFunction::GlobalFunction()
{
}
	

GlobalFunction::~GlobalFunction()
{
}

std::string generate_file_name(std::string path_name,int int_dim_x,int int_dim_y)
{
	int fileindex = 0;
	std::stringstream ss;
	std::fstream _file;
	std::string dirname= "../" + path_name;
	std::string file_name_string;
	if (!_mkdir(dirname.c_str()))std::cout << "mkdir finished : Folder \""<<path_name<<"\" ready " << std::endl;//Ä¿Â¼ÒÑ´æÔÚ
	do {
		if (_file.is_open())_file.close();
		ss.clear();
		_file.clear();
		file_name_string.clear();
		ss << dirname << "/" << path_name << "_";
		if(int_dim_x!=0)ss << int_dim_x << "x" << int_dim_y << "_";
		ss << fileindex << ".txt";
		fileindex++;
		ss >> file_name_string;
		_file.open(file_name_string, std::ios::in);
	} while (_file);
	_file.close();
	return file_name_string;
}

void create_mas_task(int task_number) {
	std::ofstream __file;
	std::string string_mas_name = generate_file_name("test");
	__file.open(string_mas_name, std::ios::out | std::ios::trunc);
	if (!__file.is_open()) {
		std::cout << "file open failed" << std::endl;
		system("PAUSE");
		__file.close();
		return;
	}
	for (int i = 0; i < task_number; i++) {
		GenerateMap* map = new GenerateMap(50, 50);
		map->RandGenerateMap(0, 0.75);
		map->PrintConsole();
		map->WriteFile();
		GenerateMAS* mas = new GenerateMAS(15, map);
		mas->RandGenerateAgent();
		mas->PrintConsole();
		mas->WriteFile();
		std::cout << mas->get_mas_name()<<"\n";
		__file << mas->get_mas_name() << std::endl;
		delete map;
		delete mas;
	}
	__file.close();
	return;
}
