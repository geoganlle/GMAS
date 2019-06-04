#include "CScene.h"

void CScene::generarMap()
{
    int pos_x = 0, pos_y = 0;

    map_pixmap_scene = new CPixMapItem** [row_scene];
    for (int i=0; i<static_cast<int>(row_scene); i++)
        map_pixmap_scene[i] = new CPixMapItem* [col_scene];

    for (int i=0; i<static_cast<int>(row_scene); i++){
        for (int j=0; j<static_cast<int>(col_scene); j++){
            map_pixmap_scene[i][j] = new CPixMapItem(whiteio,j,i);
			std::stringstream tip;
			tip << (i * row_scene + j);
			std::string tips;
			tip >> tips;
			map_pixmap_scene[i][j]->setToolTip(QString::fromStdString(tips));
            map_pixmap_scene[i][j]->setOffset(pos_x,pos_y);
            this->addItem(map_pixmap_scene[i][j]);
            pos_x += 20;
        }
        pos_x = 0;
        pos_y += 20;
    }
}

void CScene::clear_path()
{
	for (int i=0 ;i<row_scene;i++)
	{
		for (int j=0;j<col_scene;j++)
		{
			if (map_pixmap_scene[i][j]->get_ColourIcon() == pregreenio|| map_pixmap_scene[i][j]->get_ColourIcon() == greenio)
			{
				map_pixmap_scene[i][j]->set_colour(whiteio);
			};
		}
	}
}

void CScene::clear_init_and_pool()
{
	for (int i = 0; i < row_scene; i++)
	{
		for (int j = 0; j < col_scene; j++)
		{
			if (map_pixmap_scene[i][j]->get_ColourIcon() == pinkio || 
				map_pixmap_scene[i][j]->get_ColourIcon() == blueio
				)
			{
				auto it = find(init_pos_pool.begin(), init_pos_pool.end(), Point(j,i));
				if (it != init_pos_pool.end())init_pos_pool.erase(it);
				auto jt = find(goal_pos_pool.begin(), goal_pos_pool.end(), Point(j,i));
				if (jt != goal_pos_pool.end())goal_pos_pool.erase(jt);
				map_pixmap_scene[i][j]->set_colour(whiteio);
			};

		}
	}
}

CScene::CScene(int rowin, int colin)
{
    row_scene = static_cast<unsigned long long>(rowin);
    col_scene = static_cast<unsigned long long>(colin);
    map_pixmap_scene = nullptr;
    curcolour=whiteio;
    generarMap();
}

CScene::~CScene()
{
    if (map_pixmap_scene){
        for (int i=0; i<static_cast<int>(row_scene); i++){
            for (int j=0; j<static_cast<int>(col_scene); j++)
                delete map_pixmap_scene[i][j];
            delete [] map_pixmap_scene[i];
        }
        delete [] map_pixmap_scene;
        map_pixmap_scene = nullptr;
    }
    row_scene=0;
    col_scene=0;
}

void CScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){

    QPointF pos = mouseEvent->lastScenePos();
    int x = pos.toPoint().x() / 20 / 1;
    int y = pos.toPoint().y() / 20 / 1;
    if (x<0 || y<0 || x>=static_cast<int>(col_scene) || y>=static_cast<int>(row_scene))return;
	if (mouseEvent->button() == Qt::RightButton) {
		if (curcolour == pinkio) {
			auto eraseindex = find(init_pos_pool.begin(), init_pos_pool.end(), Point(x, y));
			init_pos_pool.erase(eraseindex);
			curcolour = pinkio;
		}
		else if (curcolour == blueio) 
		{
			auto eraseindex = find(goal_pos_pool.begin(), goal_pos_pool.end(), Point(x, y));
			goal_pos_pool.erase(eraseindex);
			curcolour = blueio;
		}
		map_pixmap_scene[y][x]->set_colour(whiteio);
	}
    else if (mouseEvent->button()==Qt::LeftButton)
	{
		map_pixmap_scene[y][x]->set_colour(curcolour);
		if (curcolour == pinkio) { 
			init_pos_pool.push_back(Point(x,y));
			curcolour = blueio; 
		}
		else if (curcolour == blueio) 
		{
			goal_pos_pool.push_back(Point(x, y));
			curcolour = pinkio;
		}
    }
}
