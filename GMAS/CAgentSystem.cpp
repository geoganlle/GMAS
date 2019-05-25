#include "CAgentSystem.h"
#include <string>
#include "CGlobalFunction.h"
#include <set>
void CAgentSystem::print_pathpool_to_Console()
{
	std::cout <<"\npathpool print \n";
	for (auto it = path_pool.begin(); it != path_pool.end(); it++) {
		std::cout <<" path for Agent "<< it->first<< " : ";
		for (auto jt = it->second.begin(); jt != it->second.end(); jt++) {
			std::cout << *jt<<"  ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void CAgentSystem::print_pathpool_to_file(std::string filepath)
{
	std::ofstream __file;
	__file.open(filepath, std::ios::out | std::ios::trunc);
	if (!__file.is_open()) {
		std::cout << "file open failed" << std::endl;
		__file.close();
		return;
	}
	__file << "# path pool has" << path_pool.size()<< "agents\n";
	__file << "# agent agent_path \n";

	for (auto it = path_pool.begin(); it != path_pool.end(); it++) {
		__file << it->first << " ";
		for (auto jt = it->second.begin(); jt != it->second.end(); jt++) {
			__file << *jt << " ";
		}
		__file << "\n";
	}
	__file << "\n";
	__file.close();
}

int CAgentSystem::resolve_conflicts()//��̬ȫ�ִ�����ͻһ���ܽ��
{
	/*
	��ͻ������ԣ������ߵ�����
	*/
	
	auto iter1 = path_pool.begin(); iter1++;
	auto jter = iter1->second.begin(); jter += 1;
	iter1->second.insert(jter,11);
	
	std::set<int> step_cach_set;

	//ȡ���·����Ϊѭ������
	auto iter = path_pool.end(); iter--;
	for (int i = 0; i < iter->second.size(); i++){
		
		//��ÿ��ʱ��һ�α���ÿ�������嶯��
		for (auto agent_it = path_pool.begin(); agent_it != path_pool.end(); agent_it++) {

			if (i < agent_it->second.size()) {//����Խ����
				
				if (step_cach_set.count(agent_it->second.at(i))== 0) {//����ͻ�Ƿ����
					step_cach_set.insert(agent_it->second.at(i));//��ͻδ����
				}
				else {
					int before_int = i - 1 >= 0 ? i - 1 : 0; 
					if (step_cach_set.count(agent_it->second.at(before_int)) == 0) {//��ͻ�Ƿ����
						step_cach_set.insert(agent_it->second.at(before_int));//��ͻδ����
						
					}
					else {
						//��ͻ����
						agent_it->second.insert(agent_it->second.begin() + i, agent_it->second.at(before_int));
						conflict_num++;
					}
				}
			}
		}
		step_cach_set.clear();
	}
	cost_time = clock() - this->begintime;
	return 0;
}


CAgentSystem::CAgentSystem(std::string pathname)
{
	this->gridmap = nullptr;
	this->distance = nullptr;
	std::string	line_string;
	std::ifstream	file(pathname);
	std::vector<std::vector<int>> agent_input_pool;
	std::string	map_file_path_name;
	if (file.is_open()) {
		while (std::getline(file, line_string) && line_string.size()) {//��һ���г��Ȳ�Ϊ0
			if (line_string[0] == '#')continue;
			if (line_string[0] == '.'|| line_string[0] == 'C') {
				map_file_path_name = line_string;
				continue; 
			}
			std::vector<int> intpool=string_spilt_to_int(line_string);
			agent_input_pool.push_back(intpool);
		}
		file.close();
	}
	else {
		std::cout << "ERROR: Could not open file " + pathname << std::endl;;
	}

	gridmap = new CGridMap(map_file_path_name);
	distance = new CDistance(gridmap,false);

	for (auto it = agent_input_pool.begin(); it != agent_input_pool.end(); it++) {
		if ((*it).size() != 4)continue;
		CAgent* agent = new CAgent(static_cast<int>(it - agent_input_pool.begin()),
			stPoint((*it)[0], (*it)[1]),
			stPoint((*it)[2], (*it)[3]),
			gridmap, distance
		);
		agent_pool.push_back(agent);
	}

	begintime = clock();
	this->conflict_num = 0;
	this->cost_expand = 0;
	this->cost_time = 0;

	cost_time = clock() - this->begintime;
}

CAgentSystem::~CAgentSystem()
{
	delete distance;
	delete gridmap;
	path_pool.clear();
	for (auto it = agent_pool.begin();it!=agent_pool.end();it++)
	{
		delete *it;
	}
	agent_pool.clear();
	//std::cout << "~CAgentSystem : CAgentSystem destructed\n" << std::endl;
}

int CAgentSystem::run()
{/*	
	agent_pool
	path_pool
 */
	vector <bool> finish(agent_pool.size(),false);
	bool continueloop=true;
	while (continueloop) {
		for (auto it = agent_pool.begin(); it != agent_pool.end(); it++) {
			if (finish[it - agent_pool.begin()] == false) {
				int temp_search_result = (*it)->search_step();
				if (temp_search_result == 1 || temp_search_result == 2) {
					this->cost_expand += (*it)->get_expand_node_count();
					path_pool.insert(pair <int, std::vector<int>>((*it)->get_agent_id(), (*it)->get_path()));
					finish[it - agent_pool.begin()] = true;
				};
			}
			if (it == agent_pool.end()-1) {
				auto jt = finish.begin();
				for (; jt != finish.end(); jt++) {
					if ((*jt) == false) {
						continueloop = false;
						break;
					}
				}
				continueloop = (continueloop == false) ? true : false;
			}
		}
	}
	return cost_expand; 
}
