#include "CAgentSystem.h"
#include <string>
#include "CGlobalFuntion.h"
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

int CAgentSystem::resolve_conflicts()
{
	/*
	冲突处理策略：开销高的优先
		1 2 4
		1 2 3 4 5
		1 2 4 5 6 5
	
	*/
	bool conflicts = false;
	for (auto it = path_pool.begin(); it != path_pool.end(); it++) {
		for (auto jt = it->second.begin(); jt != it->second.end(); it++) {

		
		}
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
		while (std::getline(file, line_string) && line_string.size()) {//读一行行长度不为0
			if (line_string[0] == '#')continue;
			if (line_string[0] == '.') { 
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
