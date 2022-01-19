#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#define PI 3.14159265
using namespace sf;

class Enemy
{
private:
    float xPos,yPos,xTar,yTar,speed=0.08;
public:
    Enemy();
    ~Enemy();
    void Progress(Sprite &enemy);
    void move();
    void getPoint(Vector2f point);
    void setPos( float xPos,float yPos);
    
};

Enemy::Enemy()
{
  
}

void Enemy::setPos(float xPos, float yPos)
{
    this->xPos=xPos;
    this->yPos=yPos;
}
void Enemy::move()
{
    if(xPos<xTar)xPos+=speed;
    if(xPos>xTar)xPos-=speed;
    if(yPos<yTar)yPos+=speed;
    if(yPos>yTar)yPos-=speed;
}
void Enemy::getPoint(Vector2f point)
{
   xTar=point.x;
   yTar=point.y;
}
void Enemy::Progress(Sprite &enemy)
{

    move();
    Vector2f curPos(xPos,yPos);
    enemy.setOrigin(100,100);
    float dx = curPos.x - xTar;
    float dy = curPos.y - yTar;

    float rotation = (atan2(dy,dx)) * 180 / PI;
    rotation+=270;
  
    
    Vector2f pos(xPos,yPos);
    enemy.setPosition(xPos,yPos);
    enemy.setRotation(rotation);
    
}
Enemy::~Enemy()
{
}
