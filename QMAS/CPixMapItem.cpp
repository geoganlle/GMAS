#include "CPixMapItem.h"


CPixMapItem::CPixMapItem(ColourIcon cin, int xin, int yin)
{
	colour = cin;
	x = xin;
	y = yin;
    set_colour(cin);
    set_location(xin,yin);
}

CPixMapItem::~CPixMapItem()
{
}

void CPixMapItem::set_colour(ColourIcon colourin)
{
    colour=colourin;
    QString path =  QDir::currentPath();
    //std::cout<<path.toStdString()<<std::endl;
    path="C:\\Users\\guzhe\\Desktop\\GMAS\\resources\\"+ColourIconName[colour]+".png";
    setPixmap(path);
}
