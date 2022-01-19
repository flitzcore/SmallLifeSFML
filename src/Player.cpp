#include "Player.h"
#include <math.h>

Player::Player(sf::Texture* texture,sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime =0.0f;
    currentImage.x=0;

    plRect.width = texture->getSize().x / float (imageCount.x);
    plRect.height = texture->getSize().y / float (imageCount.y);
}

Player::~Player()
{
}

void Player::Update(int row, float deltaTime)
{
    currentImage.y= row;
    totalTime+=deltaTime;

    if(totalTime>=switchTime)
    {
        totalTime-=switchTime;
        currentImage.x++;

        if(currentImage.x>=imageCount.x)
        {
            currentImage.x=0;
        }
    }
    plRect.left=currentImage.x*plRect.width;
    plRect.top=currentImage.y*plRect.height;
}

