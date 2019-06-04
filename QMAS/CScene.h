#pragma once
#include <qgraphicsscene.h>
#include <QGraphicsSceneMouseEvent>
#include "CPixMapItem.h"
#include <sstream>
struct Point
{
	int x;
	int y;
	Point(int xin, int yin) :x(xin), y(yin) {};
	bool operator==(const Point& compare) {
		return compare.x == x && compare.y == y;
	}
};

class CScene :
	public QGraphicsScene
{
private:
    CPixMapItem*** map_pixmap_scene;
    unsigned long long row_scene,col_scene;//地图尺寸
    ColourIcon curcolour;
    void generarMap();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
public:

	std::vector <Point> init_pos_pool;//起始点集
	std::vector <Point> goal_pos_pool;//目标点集

    CPixMapItem*** get_map();
    ColourIcon get_curcolour();
    void set_curcolour(ColourIcon colourin);
    unsigned long long get_row();
    unsigned long long get_col();
	
	void clear_path();
	void clear_init_and_pool();

    CScene(int rowin,int colin);
	~CScene();
};
inline CPixMapItem*** CScene::get_map(){
    return map_pixmap_scene;
};
inline ColourIcon CScene::get_curcolour(){
    return curcolour;
}
inline void CScene::set_curcolour(ColourIcon colourin){
    curcolour=colourin;
}
inline unsigned long long CScene::get_row(){
    return row_scene;
};
inline unsigned long long CScene::get_col(){
    return col_scene;
};
