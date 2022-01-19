#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>

void ParticleConstDrop(sf::Sprite& sprite,sf::Vector2f newPos)
{
      
    float sc=(10+(rand()%30))/100.0f;

    float angle=rand()%360;
    
    
    float rectX=(rand()%4)*200;

    sf::Vector2f scale(sc,sc);
    sf::IntRect rect(rectX,0,200,200);

        
    sprite.setOrigin(132,132);
    sprite.setScale(scale);
    sprite.setRotation(angle);
    sprite.setPosition(newPos);
    sprite.setTextureRect(rect);
}