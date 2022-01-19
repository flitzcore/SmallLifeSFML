#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#define PI 3.14159265
using namespace sf;

float getAlpha(float a,float b,float c)
{
    float abc=(b*b)+(c*c)-(a*a);
    float bc_2=2*b*c;
    return acos(abc/bc_2)* 180 / PI;
}
float getBeta(float a,float b,float c)
{
    float abc=(a*a)+(c*c)-(b*b);
    float ac_2=2*a*c;
    return acos(abc/ac_2)* 180 / PI;
}
float getCharlie(float alpha,float beta)
{
    return 180-(alpha+beta);
}
float PointAtMouse(Sprite &sprite,Vector2f &position)
{
    Vector2f curPos = sprite.getPosition();
  
    float dx = curPos.x - position.x;
    float dy = curPos.y - position.y;

    float rotation = (atan2(dy,dx)) * 180 / PI;//atan(dy/dx)
    
    return rotation+180;
}
float DistanceToMouse(Sprite &sprite,Vector2f &position)
{
    Vector2f curPos = sprite.getPosition();

    float dx = curPos.x - position.x;
    float dy = curPos.y - position.y;

    float distance=sqrt((dx*dx)+(dy*dy));
    return distance;
}
class Hand
{
private:
    RectangleShape rect1;
    float a=30.0f;
    RectangleShape rect2;
    float b=35.0f;
    RectangleShape rect3;
    bool DRAG=false;
    float c;
    RectangleShape rect4;
    float d;
    Vector2f position;
    Vector2f posA;
    Vector2f posB;
    Vector2f posC;
    float speed=0.1f;
public:
    Hand(/* args */);
    ~Hand();
    void handUpdate(Sprite &mc,Sprite &arm1,Sprite &arm2, Window &window,bool &TURN)
    {
        Vector2f rectSize(a,1.0f);
        rect1.setSize(rectSize);
        Vector2f rectSize2(b,1.0f);
        rect2.setSize(rectSize2);
         arm1.setPosition(mc.getPosition().x,mc.getPosition().y);
        Vector2f posM;
       

        if(Mouse::isButtonPressed(Mouse::Left)&&!DRAG) 
        {
            Vector2f mouse_pos(Mouse::getPosition(window));
   
            d=DistanceToMouse(arm1,mouse_pos);
            if(d>=65)d=65;
            Vector2f rectSize4(d,1.0f);
            rect4.setSize(rectSize4);
            
            rect4.setRotation(PointAtMouse(arm1,mouse_pos));
            rect4.setPosition(arm1.getPosition());
            DRAG=true;

        }
        if(!DRAG)
        {
            
            position= Vector2f(Mouse::getPosition(window)) ;
            c=DistanceToMouse(arm1,position);
           
      
            if(c>65)c=65;
        
        }
        else
        {
            posM=(rect4.getTransform().transformPoint(rect4.getPoint(2)));
            
            
            if(mc.getPosition().y>posM.y) mc.move(0,-speed);
            if(mc.getPosition().y<posM.y) mc.move(0,speed);
            if(mc.getPosition().x>posM.x) mc.move(-speed,0);
            if(mc.getPosition().x<posM.x) mc.move(speed,0);
            c=DistanceToMouse(mc,posM);
            
            if(c<=3)
            {
                DRAG=false;
                TURN=false;
            }
        }
        
        float alpha= getAlpha(a,b,c);
        float beta= getBeta(a,b,c);
        float charlie=getCharlie(alpha,beta);
        
        rect3.setRotation(PointAtMouse(arm1,position));
        rect3.setPosition(arm1.getPosition());
        Vector2f rectSize3(c,1.0f);
        rect3.setSize(rectSize3);

        arm1.setRotation(rect3.getRotation()+80+beta);

        rect1.setPosition(arm1.getPosition());
        rect1.setRotation(arm1.getRotation()-80);
        Vector2f armPos(rect1.getTransform().transformPoint(rect1.getPoint(2)));
        arm2.setPosition(armPos);
        arm2.setRotation(arm1.getRotation()-(170-charlie));

        rect2.setPosition(arm2.getPosition());
        rect2.setRotation(arm2.getRotation()-90);
  
        posA=(rect3.getTransform().transformPoint(rect3.getPoint(2)));
        posB=arm1.getPosition();
        posC=armPos;
    }
};

Hand::Hand(/* args */)
{
}

Hand::~Hand()
{
}

