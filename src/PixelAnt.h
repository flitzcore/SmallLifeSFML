#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class PixelAnt
{
private:
    float xPos,yPos,xTar,yTar,speed=0.1;
    
    
public:
    bool DEAD=false;
    PixelAnt(float xPos, float yPos);
    void Progress(Sprite &pxAnt);
    void move();
    void getPoint();
    void killed();
    
    ~PixelAnt();
};

PixelAnt::PixelAnt(float xPos, float yPos)
{
    this->xPos=xPos;
    this->yPos=yPos;

}

void PixelAnt::move()
{
    if(xPos<xTar)xPos+=speed;
    if(xPos>xTar)xPos-=speed;
    if(yPos<yTar)yPos+=speed;
    if(yPos>yTar)yPos-=speed;
}
void PixelAnt::killed()
{
    DEAD=true;
    
}
void PixelAnt::Progress(Sprite &pxAnt)
{
    if(!DEAD)
    {
    move();
    Vector2f curPos(xPos,yPos);
  
    float dx = curPos.x - xTar;
    float dy = curPos.y - yTar;

    float rotation = (atan2(dy,dx)) * 180 / PI;
    rotation+=270;
  
    
    Vector2f pos(xPos,yPos);
    pxAnt.setPosition(xPos,yPos);
    pxAnt.setRotation(rotation);
    }
}
void PixelAnt::getPoint()
{
   Vector2f randomPos(rand()%1000,rand()%640);
   xTar=randomPos.x;
   yTar=randomPos.y;
}

PixelAnt::~PixelAnt()
{
}
