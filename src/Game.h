#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
using namespace sf;
int once=0;
void setGame(int &LEVEL,int &enemyCount,Sprite &portal,Texture &enemy_texture, IntRect &enemy_rect,std::vector<Sprite> &enemySprite,std::vector<Enemy> &enemyArr,float &enemyDuration, int &darkScale,std::vector<CircleShape> &enemyHitBox,CircleShape &enemyCir)
{
     if(LEVEL==0)
    {
        
        if(once==0)
        {
            enemyCount=2;
            portal.setPosition(900,300);

            for(int i=0;i<enemyCount;i++)
            {
                Sprite enemy(enemy_texture,enemy_rect);
                
                enemy.setOrigin(140,194);
                enemy.setScale(0.7,0.7);
                Enemy enemyCur;
                
                enemyHitBox.push_back(enemyCir);
                enemySprite.push_back(enemy);
                enemyArr.push_back(enemyCur);
            }
            enemyArr[0].setPos(1000.0f,620.0f);
            enemyArr[1].setPos(100,100);
            enemyDuration=1;
            once++;
        }
        
    }
    else if(LEVEL==1)
    {
        if(once==1)
        {
            enemyCount=5;
            portal.setPosition(0,300);
            
            for(int i=0;i<enemyCount;i++)
            {
                Sprite enemy(enemy_texture,enemy_rect);
                enemy.setOrigin(140,194);
                enemy.setScale(0.7,0.7);
                Enemy enemyCur;
              
                enemyHitBox.push_back(enemyCir);
                enemySprite.push_back(enemy);
                enemyArr.push_back(enemyCur);
            }
            enemyArr[0].setPos(1000.0f,620.0f);
            enemyArr[1].setPos(100,100);
            enemyArr[2].setPos(0,640);
            enemyArr[3].setPos(100,640);
            enemyArr[4].setPos(1000,640);
            enemyDuration=1;
            once++;
        }
    }
    else if(LEVEL==2)
    {
        if(once==2)  
        {
            enemyCount=5;
            portal.setPosition(900,300);
        
            for(int i=0;i<enemyCount;i++)
            {
                Sprite enemy(enemy_texture,enemy_rect);
                enemy.setOrigin(140,194);
                enemy.setScale(0.7,0.7);
                Enemy enemyCur;
              
                enemyHitBox.push_back(enemyCir);
                enemySprite.push_back(enemy);
                enemyArr.push_back(enemyCur);
            }
            enemyArr[0].setPos(1000.0f,0);
            enemyArr[1].setPos(100,0);
            enemyArr[2].setPos(0,0);
            enemyArr[3].setPos(400,0);
            enemyArr[4].setPos(500,0);
            enemyDuration=1;
            darkScale=1;
            once++;
        }
    }
}