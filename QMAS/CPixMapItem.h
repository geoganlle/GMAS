#pragma once
#include <QGraphicsPixmapItem>
#include <QDir>
#include <iostream>

typedef enum { whiteio,greyio,pinkio,blueio,greenio,pregreenio,redio  } ColourIcon;
const static QString ColourIconName[7]{ "whiteio","greyio","pinkio","blueio","greenio","pregreenio","redio" };
typedef enum { passable, obstacle, origin, destination, path, expand, conflict } ColourMean;
typedef enum { E, S, W, N, NE, NW, SE, SW } Direction;

class CPixMapItem :
	public QGraphicsPixmapItem
{
	int x, y;
	ColourIcon colour;
public:
    CPixMapItem(ColourIcon cin = whiteio, int xin = 0, int yin = 0);
	~CPixMapItem();

	int get_x();
	int get_y();
	void set_location(int x, int y);//设置坐标
    ColourIcon get_ColourIcon();
	void set_colour(ColourIcon colourin);
	bool is_obstaculo();//是否为障碍物
};
inline int CPixMapItem::get_x()
{
	return x;
}
inline int CPixMapItem::get_y()
{
	return y;
}

inline void CPixMapItem::set_location(int xin, int yin)
{
	x = xin;
	y = yin;
}

inline ColourIcon CPixMapItem::get_ColourIcon()
{
    return colour;
}

inline bool CPixMapItem::is_obstaculo()
{
    return colour == static_cast<int>(obstacle) ? true : false;
}
