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
	int int_dim_x;//��ͼ�ߴ�
	int int_dim_y;
	int** int_map;//��ͼ���� 0�ϰ��� 1��ͨ�� -1����չ
	std::string string_map_name;//д���ļ�������

	std::string generateMapName();//�����ļ���
public:
	/*������ɵ�ͼ
	maptype �ϰ������� 0:�� 1:ͼ�� 2:�Թ� 
	density: ��ͨ���� �����ϰ����ı���*/
	bool RandGenerateMap(const int& maptype= 0, const double& density = 0.4);
public:
	int getDimx();
	int getDimy();
	GenerateMap();
	GenerateMap(const int& dimx, const int& dimy);
	~GenerateMap();
	bool WriteFile();//д���ļ�
	bool PrintConsole();//����̨���

	inline bool checkNodeInput(const int& x,const int& y);//��������Ƿ�Խ��
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
