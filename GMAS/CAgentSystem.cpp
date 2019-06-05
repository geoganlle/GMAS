#include "CAgentSystem.h"
#include <string>
#include "CGlobalFunction.h"
#include <set>
#include <algorithm> 
void CAgentSystem::print_map_to_console()
{
	gridmap->printGridMap();
}
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
	__file << "# path pool has " << path_pool.size()<< " agents\n";
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

int CAgentSystem::resolve_conflicts()//静态全局处理，冲突一定能解决
{
	/*
	冲突处理策略：开销低的优先
	*/
		
	std::set<int> step_cach_set;
	int result_last_conflicts = 0;//未解决冲突数
	//取最长的路径作为循环次数
	auto iter = path_pool.end(); iter--;
	for (int i = 0; i < iter->second.size(); i++){
		//step_cach_set.clear();
		//对每个时刻一次遍历每个智能体动作
		for (auto agent_it = path_pool.begin(); agent_it != path_pool.end(); agent_it++) {

			if (i < agent_it->second.size()) {//数组越界检查
				
				if (step_cach_set.count(agent_it->second.at(i))== 0) {//检查冲突是否出现
					step_cach_set.insert(agent_it->second.at(i));//冲突未出现
					int j = i - 2;
					if (j >= 0)step_cach_set.erase(agent_it->second.at(j));
				}
				else {
					int before_int = i - 1 >= 0 ? i - 1 : 0; 
					if (step_cach_set.count(agent_it->second.at(before_int)) == 0) {//冲突是否出现
						step_cach_set.insert(agent_it->second.at(before_int));//冲突未出现
						agent_it->second.insert(agent_it->second.begin() + i, agent_it->second.at(before_int));
						conflict_num++;
					}
					else {
						//前一时刻的位置已占用
						conflict_num++;
						result_last_conflicts++;
					}
				}
			}
		}
	}
	cost_time = clock() - this->begintime;
	return result_last_conflicts;
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

int CAgentSystem::Static_run()
{
	vector <bool> finish(agent_pool.size(),false);
	bool continueloop=true;
	while (continueloop) {
		for (auto it = agent_pool.begin(); it != agent_pool.end(); it++) {
			if (finish[it - agent_pool.begin()] == false) {
				int temp_search_result = (*it)->search_step();
				if (temp_search_result == 1 || temp_search_result == 2|| temp_search_result==3) {
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

int CAgentSystem::Dynamic_run()
{
	//返回值 0:成功 | -1:死锁 | -2 可替换路径不存在
	Static_run();//初始化路径
	std::set<int> step_cach_set;
	int result_last_conflicts = 0;//未解决冲突数
	int path_max_longth = 0;
	int check_count = 0;
todo:
	check_count++;
	if (check_count>path_pool.size()*2) {//假设每个最多存在两个独立冲突
		cost_time = clock() - this->begintime;
		return -1;
	}
	step_cach_set.clear();
	//调整检查冲突的循环总次数
	auto pathmaxlength = std::max_element(path_pool.begin(),path_pool.end(), 
		[](pair<int,std::vector<int>> l, pair<int, std::vector<int>> r) {
			return l.second.size() < r.second.size();
		});
	path_max_longth = static_cast<int>(pathmaxlength->second.size());
	for (int i = 0; i < path_max_longth; i++) {
		//检查每个智能体
		for (auto pathpool_it = path_pool.begin(); pathpool_it != path_pool.end(); pathpool_it++) {
			if (i >= pathpool_it->second.size())continue;//数组越界检查
			//删除最后两个
			if (i == (pathpool_it->second.size() - 1)) {
				step_cach_set.erase(pathpool_it->second.at(i));
				int j = i - 1;
				if (j >= 0)step_cach_set.erase(pathpool_it->second.at(j));
			}
			//检查冲突是否出现
			if (step_cach_set.count(pathpool_it->second.at(i)) == 0) { 
				//冲突未出现
				step_cach_set.insert(pathpool_it->second.at(i));
				//避免"擦肩而过"
				int eraseindex = i - 2;
				if (eraseindex >= 0)step_cach_set.erase(pathpool_it->second.at(eraseindex));
			}
			else {
				conflict_num++;
				//冲突已出现
				vector<int> gorge = gridmap->get_gorge(pathpool_it->second.at(i));
				stPoint initpoint = pathpool_it->second.front();//替换路径的开始节点 初始化
				stPoint goalpoint = pathpool_it->second.back();	//替换路径的最终节点
				//开始节点为峡谷中最先在路径中出现的点
				for (auto conflict_begin = pathpool_it->second.begin()+1; conflict_begin != pathpool_it->second.end(); conflict_begin++)
				{
					auto findindex = find(gorge.begin(), gorge.end(), *conflict_begin);
					if (findindex != gorge.end())
					{
						initpoint = gridmap->unhash(*(conflict_begin-1));
						break;
					}
				}
				for (auto conflict_end = pathpool_it->second.rbegin()+1; conflict_end != pathpool_it->second.rend(); conflict_end++)
				{
					auto findindex = find(gorge.begin(), gorge.end(), *conflict_end);
					if (findindex != gorge.end())
					{
						goalpoint = gridmap->unhash(*(conflict_end-1));
						break;
					}
				}
				CAgent *childAgent=new CAgent(-1, initpoint,goalpoint,gridmap,distance);
				int search_result  = childAgent->search_step(gorge);
				cost_expand += childAgent->get_expand_node_count();
				if (search_result != 1) { //子节点查找失败
					cost_time = clock() - this->begintime;
					return -2; 
				}
				
				//std::cout <<"CAgent end search" <<clock() - this->begintime << std::endl;
				vector<int> childAgent_path = childAgent->get_path();//起点和终点之间的串进行替换
				delete childAgent;
				auto erasebegin = std::find(pathpool_it->second.begin(), pathpool_it->second.end(), gridmap->hashpt(initpoint));
				auto eraseend = std::find(pathpool_it->second.begin(), pathpool_it->second.end(), gridmap->hashpt(goalpoint));
				if (eraseend - erasebegin < 2)return -1;//无法解决该冲突
				pathpool_it->second.erase(erasebegin+1,eraseend);
				eraseend = std::find(pathpool_it->second.begin(), pathpool_it->second.end(), gridmap->hashpt(goalpoint));
				if(childAgent_path.size()>2)
				pathpool_it->second.insert(eraseend,childAgent_path.begin()+1,childAgent_path.end()-1);
				resolve_self_loop(pathpool_it->second);				
				//解决冲突之后重新进行冲突检测
				goto todo;
			}
		}
	}	
	cost_time = clock() - this->begintime;
	return 0;
}
 