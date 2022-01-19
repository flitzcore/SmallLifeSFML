#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;

public:
    Player(sf::Texture* texture,sf::Vector2u imageCount, float switchTime);
    ~Player();

    void Update(int row, float deltaTime);
    
    
   
    sf::IntRect plRect;
};

