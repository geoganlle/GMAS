#include "CBfs.h"

CBfs::CBfs(const stPoint& o, const stPoint d, CGridMap* g)
	: orig_stPoint(o),dest_stPoint(d),gridmap_CGridMapp(g)
{
	soln_cost_int = INT_MAX;
	this->dim_stPoint = g->getDim();
	visited_length_int = dim_stPoint.x * dim_stPoint.y;
	visited_boolp = new bool[visited_length_int]();//Ĭ�ϳ�ʼ��Ϊfalse(0)

	if (gridmap_CGridMapp->passable(orig_stPoint) &&
		gridmap_CGridMapp->passable(dest_stPoint) ){
		search();
	}

}


CBfs::~CBfs()
{
	delete[] visited_boolp;
}

void CBfs::search()
{
	std::queue<stPointBFS> node_queue;
	node_queue.push(stPointBFS(orig_stPoint, WAIT, 0));
	visited_boolp[gridmap_CGridMapp->hashpt(orig_stPoint)] = true;
	while (!node_queue.empty()) {
		stPointBFS curNode = node_queue.front();
		node_queue.pop();
		//std::cout << "\nlog pop" << gridmap_CGridMapp->hashpt(&curNode.p_stPoint)<<"depth:"<< curNode.depth_int << std::endl;
		if (curNode.p_stPoint.x == dest_stPoint.x && 
			curNode.p_stPoint.y == dest_stPoint.y) {
			soln_cost_int = curNode.depth_int;
			return;
		}

		bool* eighborhood = gridmap_CGridMapp->getNeighbor(curNode.p_stPoint);
		if (eighborhood) {
			for (int i = 0; i < DIM; i++) {//����8���ھ�
				stPoint child = dir_move_stPoint((curNode.p_stPoint), i);

				int child_hash = child.y * dim_stPoint.x + child.x;

				//std::cout << " dir " << dir_to_string(i) <<" eighborhood[i] "<< eighborhood[i] << " y" << child.y << " x" << child.x << " hash" << child_hash;
				//std::cout << " vis " << visited_boolp[child_hash]<< " i " <<i << "curdir "<<curNode.dir_int;
				if (//gridmap_CGridMapp->passable(child) &&//�ӽڵ��ͨ��
					i != curNode.dir_int && //δ���ʹ��Ҳ�Ϊ��ʱ�ķ���
					eighborhood[i] &&
					!visited_boolp[child_hash]
					) {// �ӽڵ����ϰ���
					int to_parent_dir = dir_reverse(i);
					int depth = curNode.depth_int + 1;
					node_queue.push(stPointBFS(child, to_parent_dir, depth));
					//std::cout << " push "<< child_hash ;
					visited_boolp[child_hash] = true;	//��ʼ��ʱĬ����false
				}
				//std::cout << "\n";
			}
			//std::cout << "end line \n";
		}
		delete[] eighborhood;
	}
}
