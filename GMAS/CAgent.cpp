#include "CAgent.h"

CAgent::CAgent(int agentid_i, stPoint init_i, stPoint goal_i, CGridMap* gridmap_i,CDistance* cdistance_i)
	:agentid(agentid_i),init(init_i),goal(goal_i),gridmap(gridmap_i),cdistance(cdistance_i)
{
	stSearch_Node temp(init,agentid,0,INT_MAX,WAIT);

	search_node_pool.push_back(temp);
	sort(search_node_pool.begin(), search_node_pool.end(),
		[](const stSearch_Node & node_left, const stSearch_Node & node_right) -> int {
			return node_left.fn < node_right.fn;
		});
	visited.resize(gridmap->getDim().x * gridmap->getDim().y );
	visited[gridmap->hashpt(&temp.location)]=true;

	search_count = 0;
	expand_node_count = 0;
}

CAgent::~CAgent()
{
	this->close_search_node_pool.clear();
	this->search_node_pool.clear();
	this->path_hash.clear();
}

int CAgent::search_step()
{
	if (search_count > MAX_SEARCH_COUNT)return 2;
	search_count++;
	/*
	for (auto it = search_node_pool.begin(); it != search_node_pool.end(); it++) {
		std::cout << "search_node_pool " << " first " << it->first << "  ";
	}
	std::cout << "\n";
	*/
	stSearch_Node curnode = search_node_pool.front();
	visited[gridmap->hashpt(&curnode.location)] = true;
	search_node_pool.erase(search_node_pool.begin());
	close_search_node_pool.push_back(curnode);

	if (curnode.location == goal)return 1;

	bool * neighbor_node = gridmap->getNeighbor(curnode.location);

	if(neighbor_node!=NULL)
	for (int i = 0; i < DIM;i++) {
		stSearch_Node expandnode;
		expandnode.location = dir_move_stPoint(curnode.location, i);
		if (i == (curnode.dir_to_parent) ||//来时方向
			neighbor_node[i]==0 || //不可达
			visited[gridmap->hashpt(&expandnode.location)]==true)//已访问过
		{
			/*
			std::cout << " A " << ( i == (curnode.dir_to_parent))?1:0;
			std::cout << " B " << (!neighbor_node[i]==0)?1:0;
			std::cout << " C " << (visited[gridmap->hashpt(&expandnode.location)]==1)?1:0;
			std::cout << "\n";
			*/
			continue;//跳过
		}

		expandnode.agentid = agentid;
		expandnode.dir_to_parent = dir_reverse(i);
		expandnode.gn = curnode.gn + 1;
		int dis = cdistance->getDistance(expandnode.location, goal);
		expandnode.hn =	( dis == INT_MAX ) ? h(expandnode.location,goal):dis;
		expandnode.fn = expandnode.gn + expandnode.hn;
		
		search_node_pool.push_back(expandnode);

		expand_node_count++;
		//visited[gridmap->hashpt(&expandnode.location)] = true;
		
		///TODO:
		/*
		更新cdistance表
		cdistance->setDistance(init,expandnode.location,expandnode.gn);
		*/

		/*
		std::cout << " A " << (i == (curnode.dir_to_parent)) ? 1 : 0;
		std::cout << " B " << (neighbor_node[i] == 1) ? 1 : 0;
		std::cout << " C " << (visited[gridmap->hashpt(&expandnode.location)] == 1) ? 1 : 0;
		std::cout << "\n";
		*/
	}
	sort(search_node_pool.begin(), search_node_pool.end(),
		[](const stSearch_Node & node_left, const stSearch_Node & node_right) -> int {
			return node_left.fn < node_right.fn;
		});

	delete[] neighbor_node;
	return 0;
}

int CAgent:: h(const stPoint& init, const stPoint& goal, CGridMap* gridmap)
{
	CBfs bfs(&stPoint(init.x,init.y), &stPoint(goal.x, goal.y), gridmap);
	return  bfs.get_soln_cost_int();
}

std::vector<int> CAgent::get_path()
{
	
	if (close_search_node_pool.empty())return path_hash;

	stSearch_Node curnode = close_search_node_pool.back();
	close_search_node_pool.pop_back();
	path_hash.push_back(gridmap->hashpt(&curnode.location));
	do {
		stPoint parent_point = dir_move_stPoint(curnode.location, curnode.dir_to_parent);
		if(!close_search_node_pool.empty())
		for (auto it = close_search_node_pool.begin(); it != close_search_node_pool.end(); it++) {
			if (it->location == parent_point) {
				curnode = *it;
				path_hash.push_back(gridmap->hashpt(&parent_point));
				close_search_node_pool.erase(it);
				break;
			}
		};
	} while (!(curnode.location == init));
	//path_hash.push_back(gridmap->hashpt(&init));
	return path_hash;
}
