#include "CAgentSystem.h"
#include <string>
#include "CGlobalFuntion.h"
void CAgentSystem::print_pathpool_to_Console()
{
	std::cout <<"\n pathpool print \n";
	for (auto it = pathpool.begin(); it != pathpool.end(); it++) {
		std::cout <<" path for Agent "<< it->first<< " : ";
		for (auto jt = it->second.begin(); jt != it->second.end(); jt++) {
			std::cout << *jt<<" ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
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
		Agent_pool.push_back(agent);
	}

	begintime = clock();
	this->conflict_num = 0;
	this->cost_expand = 0;
	this->cost_time = 0;

}

CAgentSystem::~CAgentSystem()
{
}

int CAgentSystem::run()
{/*	
	Agent_pool
	pathpool
 */
	while (!Agent_pool.empty()) {
		for (auto it = Agent_pool.begin(); it != Agent_pool.end(); it++) {
			(*it)->get_expand_node_count();
			switch ((*it)->search_step()) {
			case 1:
				pathpool.insert(pair <int, std::vector<int>>((*it)->get_agent_id(), (*it)->get_path()));
				this->cost_expand+= (*it)->get_expand_node_count();
				Agent_pool.erase(it);
				break;
			case 2:
				//TODO:异常处理
				pathpool.insert(pair <int, std::vector<int>>((*it)->get_agent_id(), (*it)->get_path()));
				Agent_pool.erase(it);
				break;
			default:;
			}
		}
	}
	return cost_expand; 
}
