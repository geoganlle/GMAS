#include "CAgent.h"

std::vector<stPoint> CAgent::get_Next_expand_node()
{
	std::vector <stPoint> resultvector;
	for (auto it = search_node_pool.begin(); 
		it != search_node_pool.end() && it - search_node_pool.begin();
		it++)
	{
		if(it->fn==search_node_pool.begin()->fn)
		resultvector.push_back(it->location);
		else break;
	}
	return resultvector;
}

CAgent::CAgent(int agentid_i, stPoint init_i, stPoint goal_i, CGridMap* gridmap_i,CDistance* cdistance_i)
	:agentid(agentid_i),init(init_i),goal(goal_i),gridmap(gridmap_i),cdistance(cdistance_i)
{
	stSearch_Node temp(init,agentid,0,INT_MAX,WAIT);

	search_node_pool.push_back(temp);//将初始点加入搜索集
	/*理论上搜索集中每加入一次节点需要重新排序，但初始化后节点集中只有一个节点，可以省略排序过程
	sort(search_node_pool.begin(), search_node_pool.end(),
		[](const stSearch_Node & node_left, const stSearch_Node & node_right) -> int {
			return node_left.fn < node_right.fn;
		});
	*/
	int resize_length = gridmap->getDim().x * gridmap->getDim().y;
	visited.resize(resize_length,false);
	visited[gridmap->hashpt(temp.location)]=true;

	search_count = 0;
	expand_node_count = 0;
}

CAgent::~CAgent()
{
	this->search_node_pool.clear();
	this->close_search_node_pool.clear();
	this->path_hash.clear();
	this->visited.clear();
	//std::cout << "~CAgent : CAgent destructed" << std::endl;
}

int CAgent::search_step()
{
	if (search_count > MAX_SEARCH_COUNT)return 2;//搜索节点过多
	if (search_node_pool.empty())return 3;//目的节点不可达
	stSearch_Node curnode = search_node_pool.front();
	visited[gridmap->hashpt(curnode.location)] = true;
	search_node_pool.erase(search_node_pool.begin());
	close_search_node_pool.push_back(curnode);
	if (curnode.location == goal)return 1;//已找到目标节点
	search_count++;//搜索计数
	bool * neighbor_node = gridmap->getNeighbor(curnode.location);
	if(neighbor_node!=NULL)
	for (int i = 0; i < DIM;i++) {
		stSearch_Node expandnode;
		expandnode.location = dir_move_stPoint(curnode.location, i);
		if (i == (curnode.dir_to_parent) ||//来时方向
			neighbor_node[i]==0 || //不可达
			visited[gridmap->hashpt(expandnode.location)]==true//已访问过
			)
		{
			continue;//跳过
		}
		expandnode.agentid = agentid;
		expandnode.dir_to_parent = dir_reverse(i);
		expandnode.gn = curnode.gn + 1;
		int dis = cdistance->getDistance(expandnode.location, goal);
		expandnode.hn =	( dis == INT_MAX ) ? h(expandnode.location,goal,gridmap):dis;
		expandnode.fn = expandnode.gn + expandnode.hn;
		visited[gridmap->hashpt(expandnode.location)] = true;
		search_node_pool.push_back(expandnode);
		expand_node_count++;
		/*更新cdistance表*/
		for (auto it= close_search_node_pool.begin();it!=close_search_node_pool.end();it++)
		{
			cdistance->setDistance(it->location, expandnode.location, expandnode.gn-it->gn);
		}
	}
	sort(search_node_pool.begin(), search_node_pool.end(),
		[](const stSearch_Node & node_left, const stSearch_Node & node_right) -> int {
			return node_left.fn < node_right.fn;
		});
	delete[] neighbor_node;
	return 0;
}
int CAgent::search_step(const std::vector<int>& ignoreNodeVector)
{
	int result = 0;
	for (auto it = ignoreNodeVector.begin(); it != ignoreNodeVector.end(); it++)
	{
		visited[*it] = true;
	}
	stSearch_Node curnode = search_node_pool.front();
	while (result==0)
	{
		if (search_count > MAX_SEARCH_COUNT) { result = 2; break;}//搜索节点过多
		if (search_node_pool.empty()) { result = 3; break; }//目的节点不可达	
		curnode = search_node_pool.front();
		visited[gridmap->hashpt(curnode.location)] = true;
		search_node_pool.erase(search_node_pool.begin());
		close_search_node_pool.push_back(curnode);		
		if (curnode.location == goal) { result = 1; break; };//已找到目标节点
		search_count++;//搜索计数
		bool* neighbor_node = gridmap->getNeighbor(curnode.location);
		if (neighbor_node != NULL)
			for (int i = 0; i < DIM; i++) {
				stSearch_Node expandnode;
				expandnode.location = dir_move_stPoint(curnode.location, i);
				if (i == (curnode.dir_to_parent) ||//来时方向
					neighbor_node[i] == 0 || //不可达
					visited[gridmap->hashpt(expandnode.location)] == true//已访问过
					)
				{
					continue;//跳过
				}
				expandnode.agentid = agentid;
				expandnode.dir_to_parent = dir_reverse(i);
				expandnode.gn = curnode.gn + 1;
				int dis = cdistance->getDistance(expandnode.location, goal);
				expandnode.hn = (dis == INT_MAX) ? h(expandnode.location, goal, gridmap) : dis;
				expandnode.fn = expandnode.gn + expandnode.hn;
				visited[gridmap->hashpt(expandnode.location)] = true;
				search_node_pool.push_back(expandnode);
				expand_node_count++;
				/*更新cdistance表*/
				for (auto it = close_search_node_pool.begin(); it != close_search_node_pool.end(); it++)
				{
					cdistance->setDistance(it->location, expandnode.location, expandnode.gn - it->gn);
				}
			}
		sort(search_node_pool.begin(), search_node_pool.end(),
			[](const stSearch_Node & node_left, const stSearch_Node & node_right) -> int {
				return node_left.fn < node_right.fn;
			});
		delete[] neighbor_node;
	}
	return result;
}
int CAgent::BFSDistance(const stPoint& init, const stPoint& goal, CGridMap* gridmap)
{
	CBfs bfs(stPoint(init.x, init.y), stPoint(goal.x, goal.y), gridmap);
	return  bfs.get_soln_cost_int();
}

int CAgent:: h(const stPoint& init, const stPoint& goal, CGridMap* gridmap)
{
	//根据地图尺寸动态选择使用哪种距离作为估值
	stPoint DimPoint = gridmap->getDim();
	int dimcompare = DimPoint.x + DimPoint.y;
	int h = ManhattanDistance(init, goal);
	if (h > (dimcompare / 3 * 2))return h;
	if (h > (dimcompare / 3))return CustomMapDistance(init,goal,DimPoint);
	return BFSDistance(init, goal, gridmap);

}

std::vector<int> CAgent::get_path()
{
	if (close_search_node_pool.empty())return path_hash;
	stSearch_Node curnode = close_search_node_pool.back();
	close_search_node_pool.pop_back();
	path_hash.push_back(gridmap->hashpt(curnode.location));
	do {
		stPoint parent_point = dir_move_stPoint(curnode.location, curnode.dir_to_parent);
		if(!close_search_node_pool.empty())
		for (auto it = close_search_node_pool.begin(); it != close_search_node_pool.end(); it++) {
			if (it->location == parent_point) {
				curnode = *it;
				path_hash.push_back(gridmap->hashpt(parent_point));
				close_search_node_pool.erase(it);
				break;
			}
		};
	} while (!(curnode.location == init));
	reverse(path_hash.begin(),path_hash.end());
	return path_hash;
}
