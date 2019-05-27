#include "CScene.h"

void CScene::generarMap()
{
    int pos_x = 0, pos_y = 0;

    map = new CPixMapItem** [row];
    for (int i=0; i<static_cast<int>(row); i++)
        map[i] = new CPixMapItem* [col];

    for (int i=0; i<static_cast<int>(row); i++){
        for (int j=0; j<static_cast<int>(col); j++){
            map[i][j] = new CPixMapItem(whiteio,j,i);
			std::stringstream tip;
			tip << (i * row + j);
			std::string tips;
			tip >> tips;
			map[i][j]->setToolTip(QString::fromStdString(tips));
            map[i][j]->setOffset(pos_x,pos_y);
            this->addItem(map[i][j]);
            pos_x += 20;
        }
        pos_x = 0;
        pos_y += 20;
    }
}

CScene::CScene(int rowin, int colin)
{
    row = static_cast<unsigned long long>(rowin);
    col = static_cast<unsigned long long>(colin);
    map = nullptr;
    curcolour=whiteio;
	//generate_goal_or_init = false;
    generarMap();

}

CScene::~CScene()
{
    if (map){
        for (int i=0; i<static_cast<int>(row); i++){
            for (int j=0; j<static_cast<int>(col); j++)
                delete map[i][j];
            delete [] map[i];
        }
        delete [] map;
        map = nullptr;
    }
    row=0;
    col=0;
}

void CScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){

    QPointF pos = mouseEvent->lastScenePos();

    int x = pos.toPoint().x() / 20 / 1;
    int y = pos.toPoint().y() / 20 / 1;

    if (x<0 || y<0 || x>=static_cast<int>(col) || y>=static_cast<int>(row))
            return;

    if (mouseEvent->button()==Qt::RightButton)
        map[y][x]->set_colour(whiteio);

    else if (mouseEvent->button()==Qt::LeftButton){
        //TODO:
		/*
		if (curcolour == pinkio || curcolour == blueio) {
			if (generate_init_or_goal) {
				
			}
			generate_init_or_goal = !generate_init_or_goal;
		}
		*/
		map[y][x]->set_colour(curcolour);
		if (curcolour == pinkio) { 
			init_pos_pool.push_back(Point(x,y));
			curcolour = blueio; 
		}
		else if (curcolour == blueio) {
			goal_pos_pool.push_back(Point(x, y));
			curcolour = pinkio;
		}
    }

}
