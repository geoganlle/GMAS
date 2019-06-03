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

	search_node_pool.push_back(temp);//����ʼ�����������
	/*��������������ÿ����һ�νڵ���Ҫ�������򣬵���ʼ����ڵ㼯��ֻ��һ���ڵ㣬����ʡ���������
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
	if (search_count > MAX_SEARCH_COUNT)return 2;//�����ڵ����
	if (search_node_pool.empty())return 3;//Ŀ�Ľڵ㲻�ɴ�
	stSearch_Node curnode = search_node_pool.front();
	visited[gridmap->hashpt(curnode.location)] = true;
	search_node_pool.erase(search_node_pool.begin());
	close_search_node_pool.push_back(curnode);
	if (curnode.location == goal)return 1;//���ҵ�Ŀ��ڵ�
	search_count++;//��������
	bool * neighbor_node = gridmap->getNeighbor(curnode.location);
	if(neighbor_node!=NULL)
	for (int i = 0; i < DIM;i++) {
		stSearch_Node expandnode;
		expandnode.location = dir_move_stPoint(curnode.location, i);
		if (i == (curnode.dir_to_parent) ||//��ʱ����
			neighbor_node[i]==0 || //���ɴ�
			visited[gridmap->hashpt(expandnode.location)]==true//�ѷ��ʹ�
			)
		{
			continue;//����
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
		/*����cdistance��*/
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
		if (search_count > MAX_SEARCH_COUNT) { result = 2; break;}//�����ڵ����
		if (search_node_pool.empty()) { result = 3; break; }//Ŀ�Ľڵ㲻�ɴ�	
		curnode = search_node_pool.front();
		visited[gridmap->hashpt(curnode.location)] = true;
		search_node_pool.erase(search_node_pool.begin());
		close_search_node_pool.push_back(curnode);		
		if (curnode.location == goal) { result = 1; break; };//���ҵ�Ŀ��ڵ�
		search_count++;//��������
		bool* neighbor_node = gridmap->getNeighbor(curnode.location);
		if (neighbor_node != NULL)
			for (int i = 0; i < DIM; i++) {
				stSearch_Node expandnode;
				expandnode.location = dir_move_stPoint(curnode.location, i);
				if (i == (curnode.dir_to_parent) ||//��ʱ����
					neighbor_node[i] == 0 || //���ɴ�
					visited[gridmap->hashpt(expandnode.location)] == true//�ѷ��ʹ�
					)
				{
					continue;//����
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
				/*����cdistance��*/
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
	//���ݵ�ͼ�ߴ綯̬ѡ��ʹ�����־�����Ϊ��ֵ
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
