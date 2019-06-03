#include "CGlobalFunction.h"



CGlobalFunction::CGlobalFunction()
{
}

CGlobalFunction::~CGlobalFunction()
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
	if (string_input.back() != ' ')
	result.push_back(temp_int);
	return result;
}

bool resolve_self_loop(vector<int>& s)
{
	int delete_end_index = -1;
	int len = static_cast<int>(s.size());
	bool flag = false;
	for (int i = 0; i < len; i++) {
		delete_end_index = -1;
		//奇数对称
		for (int j = 1; j < len; j++) {
			int le = i - j, ri = i + j;
			if (le < 0 || ri >= len || s[le] != s[ri])break;
			delete_end_index = ri;
		}
		//偶数对称
		if (delete_end_index == -1) {
			for (int j = 1; j < len; j++) {
				int le = i - j + 1, ri = i + j;
				if (le < 0 || ri >= len || s[le] != s[ri])break;
				delete_end_index = ri;
			}
		}
		if (delete_end_index != -1) {
			if (i + 1 >= len || delete_end_index + 1 > len)continue;
			s.erase(s.begin() + i + 1, s.begin() + delete_end_index + 1);
			flag = true;
			len = static_cast<int>(s.size());
		}
	}
	return flag;
}

vector<string> readfile(string filename) {

	std::string	line_string;
	std::ifstream	file(filename);
	std::vector<std::string> result_vector;

	if (file.is_open()) {
		while (std::getline(file, line_string) && line_string.size()) {//读一行行长度不为0
			result_vector.push_back(line_string);
		}
		file.close();
	}
	else {
		std::cout << "ERROR: Could not open file " + filename << std::endl;;
	}
	return result_vector;
}

void get_gorge_test() {

	CGridMap map("../cached/map.txt");
	vector<int> re = map.get_gorge(57);
	for (auto it=re.begin();it!=re.end();it++)
	{
		cout << *it<<" ";
	}
	cout << endl;
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
			cout << "搜索过量" << endl;
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
	CAgentSystem mas("../mas/10x10mas2.txt");
	mas.Static_run();
	mas.print_pathpool_to_Console();
	mas.resolve_conflicts();
	mas.print_pathpool_to_Console(); 

}

void test3()
{
	vector <string> masfilename_vector = readfile("../test/test_5.txt");
	vector <stCAgentSystem> testresult_pool;
	int resolve_count = 0;
	for (int i=0;i<masfilename_vector.size();i++)
	{
		cout << "begin instance "<<i+1<<"\n";
		CAgentSystem mas(masfilename_vector[i]);
		mas.Static_run();
		if(mas.resolve_conflicts()==0)resolve_count++;
		stCAgentSystem temp(i,mas.get_cost_time(),mas.get_cost_expand(),mas.get_conflict_num());
		testresult_pool.push_back(temp);
	}
	cout << "\n共解决了"<< resolve_count <<"/"<< masfilename_vector.size()<<"个多智能体系统\n";
	clock_t costtime = 0;
	int cost_expand = 0;
	int conflict = 0;
	for (int i = 0; i < testresult_pool.size(); i++) {
		costtime += testresult_pool[i].cost_time;
		cost_expand += testresult_pool[i].cost_expand;
		conflict += testresult_pool[i].conflict_num;
	}
	cout << "总耗时: " << costtime << " 平均耗时:"<< costtime/testresult_pool.size();
	cout << "\n总扩展节点: " << cost_expand << " 平均扩展节点:" << cost_expand / testresult_pool.size();
	cout << "\n总冲突数: " << conflict << " 平均冲突数:" << conflict / testresult_pool.size();
}

void runmas1()//静态多智能体路径规划
{
	string mas_filepath = "C:\\Users\\guzhe\\Desktop\\GMAS\\cached\\mas.txt";
	string pathpool_filepath = "C:\\Users\\guzhe\\Desktop\\GMAS\\cached\\pathpool.txt";
	CAgentSystem mas(mas_filepath);
	mas.Static_run();
	//mas.print_pathpool_to_Console();
	mas.resolve_conflicts();
	//mas.print_pathpool_to_Console();
	mas.print_pathpool_to_file(pathpool_filepath);
}
void runmas2() //动态多智能体路径规划
{
	string mas_filepath = "C:\\Users\\guzhe\\Desktop\\GMAS\\cached\\mas.txt";
	string pathpool_filepath = "C:\\Users\\guzhe\\Desktop\\GMAS\\cached\\pathpool.txt";
	CAgentSystem mas(mas_filepath);
	mas.Dynamic_run();
	mas.print_pathpool_to_file(pathpool_filepath);
}
