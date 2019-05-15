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

void test1()
{
	//test
	CGridMap map("../map/10x10map0.txt");
	CBfs a(&stPoint(0, 0), &stPoint(9, 9), &map);
	cout << "bfs cost " << a.get_soln_cost_int() << endl;
	CDistance d((&map), false);
	CAgent	agent(0, stPoint(0, 0), stPoint(9, 9), &map, &d);

	do {
		if (agent.search_step() == 2) {
			cout << "ËÑË÷¹ýÁ¿" << endl;
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
	CAgentSystem mas("../mas/20x50mas0.txt");
	mas.run();
	mas.print_pathpool_to_Console();

}
