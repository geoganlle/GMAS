#include "CGlobalFuntion.h"



CGlobalFuntion::CGlobalFuntion()
{
}

CGlobalFuntion::~CGlobalFuntion()
{
}

vector<int> string_spilt_to_int(const std::string& string_input)
{
	vector<int> result;
	int temp_int = 0;
	for (auto it = string_input.begin(); it != string_input.end(); it++) {
		if (*it == ' ')
		{
			result.push_back(temp_int);
			temp_int = 0;
		}
		else {
			temp_int = temp_int * 10 + ((*it) - '0');
		}
	}
	result.push_back(temp_int);
	return result;
}

vector<string> readfile(string filename) {

	std::string	line_string;
	std::ifstream	file(filename);
	std::vector<std::string> result_vector;

	if (file.is_open()) {
		while (std::getline(file, line_string) && line_string.size()) {//��һ���г��Ȳ�Ϊ0
			result_vector.push_back(line_string);
		}
		file.close();
	}
	else {
		std::cout << "ERROR: Could not open file " + filename << std::endl;;
	}
	return result_vector;
}

void test1()
{
	//test
	CGridMap map("../map/10x10map0.txt");
	CBfs a(stPoint(0, 0), stPoint(9, 9), &map);
	cout << "bfs cost " << a.get_soln_cost_int() << endl;
	CDistance d((&map), false);
	CAgent	agent(0, stPoint(0, 0), stPoint(9, 9), &map, &d);

	do {
		if (agent.search_step() == 2) {
			cout << "��������" << endl;
			break;
		}
		if (agent.search_step() == 1) {
			cout << "" << endl;
			break;
		}
	} while (true);

	vector <int> v = agent.get_path();
	for (auto it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
	agent.~CAgent();
}

void test2()
{
	//system("dir");
	CAgentSystem mas("../mas/10x10mas2.txt");
	mas.run();
	mas.print_pathpool_to_Console();
	switch (mas.resolve_conflicts())
	{
	case -1:;
	case -2:;
	case 0:;
	default:
		break;
	};
	mas.print_pathpool_to_Console();

}

void test3()
{
	vector <string> masfilename_vector = readfile("../test/test0.txt");
	vector <stCAgentSystem> testresult_pool;
	for (int i=0;i<masfilename_vector.size();i++)
	{
		CAgentSystem mas(masfilename_vector[i]);
		mas.run();
		mas.resolve_conflicts();
		stCAgentSystem temp(i,mas.get_cost_time(),mas.get_cost_expand(),mas.get_conflict_num());
		testresult_pool.push_back(temp);
	}
	cout << "\n�������"<< masfilename_vector.size()<<"����������ϵͳ\n";
	clock_t costtime = 0;
	int cost_expand = 0;
	int conflict = 0;
	for (int i = 0; i < testresult_pool.size(); i++) {
		costtime += testresult_pool[i].cost_time;
		cost_expand += testresult_pool[i].cost_expand;
		conflict += testresult_pool[i].conflict_num;
	}
	cout << "�ܺ�ʱ: " << costtime << " ƽ����ʱ:"<< costtime/testresult_pool.size();
	cout << "\n����չ�ڵ�: " << cost_expand << " ƽ����չ�ڵ�:" << cost_expand / testresult_pool.size();
	cout << "\n��ͻ����: " << conflict << " ƽ����ͻ��:" << conflict / testresult_pool.size();
}
