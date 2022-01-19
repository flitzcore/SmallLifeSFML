#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Particle.h"
#include "Hand.h"
#include "PixelAnt.h"
#include "Enemy.h"
#include "Game.h"
#include <SFML/Audio.hpp>




using namespace sf;


int main()
{
    RenderWindow window(VideoMode(1000,640), "Small Life");
    //////////Audio//////////
    Music mainMenuMusic;
    mainMenuMusic.openFromFile("music/MainMenu.wav");
    mainMenuMusic.play();
    mainMenuMusic.setLoop(true);
    mainMenuMusic.setVolume(50);
    Music startMusic;
    startMusic.openFromFile("music/start.wav");
    startMusic.setVolume(20);
    startMusic.setLoop(true);
    bool playStartMusic=false;
//////////////Setup////////////
    bool Trans=false;
///enemy/////
    int LEVEL=0;
    bool GameOver=false;
    int darkScale=2;
    Texture enemy_texture;
    enemy_texture.loadFromFile("image/enemy.png");
    IntRect enemy_rect(0,0,200,600);
    
    std::vector<Sprite> enemySprite;
    std::vector<Enemy>enemyArr;
    int enemyCount;
    float enemyDuration;
    std::vector<CircleShape> enemyHitBox;
    CircleShape enemyCir(10);
    
//////finish///////
    Texture portal_texture;
    portal_texture.loadFromFile("image/portal.png");
    IntRect portal_rect(0,0,396,600);
    Sprite portal;
    portal.setTexture(portal_texture);
    portal.setTextureRect(portal_rect);
    portal.setScale(0.3,0.3);
 
   
    
    //mc//
    Texture idle_texture;
    idle_texture.loadFromFile("image/idle.png");
    IntRect player_rect(264,0,264,264);
    Sprite mc(idle_texture,player_rect);
    mc.setOrigin(140,194);
    Player player(&idle_texture, Vector2u(4,1),0.3f);
    mc.setPosition(300,300);
    mc.setScale(0.7,0.7);
    CircleShape mcHitBox(20);
    //arm//
    Texture arm1_texture;
    arm1_texture.loadFromFile("image/arm1.png");
    Sprite arm1(arm1_texture);
    Texture arm2_texture;
    arm2_texture.loadFromFile("image/arm2.png");
    Sprite arm2(arm2_texture);

    arm1.setOrigin(70,158);
    arm2.setOrigin(79,158);
    arm1.setScale(0.5,0.5);
    arm2.setScale(0.5,0.5);
    //blood//
    Texture blood_texture;
    blood_texture.loadFromFile("image/blood.png");
    //Tangan
    Hand hand;
    // Darkness
    Texture dark_texture;
    dark_texture.loadFromFile("image/dark.jpg");
    Sprite dark(dark_texture);
    dark.setOrigin(1000,1000);
    ///main menu
    Texture ant_px_texture;
    ant_px_texture.loadFromFile("image/ant_px.png");
    IntRect apx_rect(0,0,228,217);
    std::vector<Sprite>antPx;
    std::vector<PixelAnt>Pix_Arr;
    for(int i=0;i<30;i++)
            {
                Sprite ant_px(ant_px_texture,apx_rect);
                ant_px.setScale(0.1,0.1);
                Vector2f randomPos(rand()%1000,rand()%640);
                PixelAnt pix(randomPos.x,randomPos.y);
                Pix_Arr.push_back(pix);
                antPx.push_back(ant_px);
            }
    int antPxSize=antPx.size();
    
///////MainMEnu/////////////
    bool START=false;
    bool TURN=true;
    
    bool antPixKilled=false;
    float antPxAlpha=255;
    float scPxAlpha=0;
    float menuMusicVolume=50;
    RectangleShape screenTransition;
    screenTransition.setSize(Vector2f(1000.0f,1000.0f));
    screenTransition.setFillColor(Color(0,0,0,scPxAlpha));
    
    Texture title_texture;
    title_texture.loadFromFile("image/judul.png");
    IntRect title_rect(0,0,700,377);
    Sprite title(title_texture,title_rect);
    title.setOrigin(Vector2f(800,200));
    title.setScale(0.4,0.4);
    title.setPosition(Vector2f(650,180));
    Texture text1_texture;
    text1_texture.loadFromFile("image/text.png");
    Sprite text1(text1_texture);
    text1.setScale(0.15,0.15);
    text1.setPosition(Vector2f(380,350));
    Texture tutor_texture;
    tutor_texture.loadFromFile("image/tutor.png");
    Sprite tutor(tutor_texture);
    tutor.setScale(0.5,0.5);
    tutor.setPosition(Vector2f(380,350));

    Texture text2_texture;
    text2_texture.loadFromFile("image/text2.png");
    Sprite text2(text2_texture);
    text2.setScale(0.3,0.3);
    text2.setPosition(Vector2f(380,350));
    text2.setColor(Color(0,0,0,0));
    


    float deltaTime=0.0f;

    Clock clock;
    Clock particle_time;
    Clock pixAntTimer;
    Clock pixAntSkin;
    Clock titleBar;
    Clock timer;
    Clock turnTimer;
    Clock transTimer;
    Clock deadTimer;
    Clock timerGameOver;
    bool gameOverTimer=false;
    bool deadTim=false;
    bool timerTrans=false;
    bool timerTurn=false;
    bool timeVal=false;
    float time_interval=0;
    int randBar;
   
    
    std::vector<Sprite>bloodVec;
    std::vector<float>bloodVecAlpha;
    
    
    while (window.isOpen())
    {
        Event event;
        deltaTime=clock.restart().asSeconds();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        
        //music
        if(playStartMusic)
            {
                startMusic.play();
                playStartMusic=false;
            }
        if(START)
        {
            //////enemy////////
            setGame(LEVEL,enemyCount,portal,enemy_texture,enemy_rect,enemySprite,enemyArr,enemyDuration,darkScale,enemyHitBox,enemyCir);
            if(mcHitBox.getGlobalBounds().intersects(portal.getGlobalBounds()))
            {
                LEVEL++;
                TURN=true;
                Trans=true;
            }
            
            int enemyCount=enemySprite.size();
            for(int i=0;i<enemyCount;i++)
            {
      
                enemyHitBox[i].setPosition(enemySprite[i].getPosition());
               if(mcHitBox.getGlobalBounds().intersects(enemyHitBox[i].getGlobalBounds()))
               {
                 if(!deadTim)
                 {
                     deadTimer.restart();
                     deadTim=true;
                 }
                if(deadTimer.getElapsedTime().asSeconds()>3)
                {
                    GameOver=true;
                }
               }
            
            }
            if(GameOver)
            {
                
                if(!gameOverTimer)
                {
                    gameOverTimer=true;
                    timerGameOver.restart();
                }
                if(timerGameOver.getElapsedTime().asSeconds()>=2)
                {
                    window.close();
                }

            }
            if(Trans)
            {
                if(!timerTrans)
                {
                    transTimer.restart();
                    startMusic.stop();
                    playStartMusic=true;
                    timerTrans=true;
                }
                if(transTimer.getElapsedTime().asSeconds() >= 1)
                {
                    Trans=false;
                    timerTrans=false;
                }
            }
            if(!TURN)
            {
                for(int i=0;i<enemyCount;i++)
                {
                    enemyArr[i].Progress(enemySprite[i]);
                    enemyArr[i].getPoint(bloodVec[2].getPosition());
                }
                if(!timerTurn)turnTimer.restart();
                timerTurn=true;
                if(turnTimer.getElapsedTime().asSeconds()>enemyDuration)
                {
                    timerTurn=false;
                    TURN=true;
                }
            }
            
           if(pixAntSkin.getElapsedTime().asMilliseconds()>500.0f)
            {
                if(enemy_rect.left<400)enemy_rect.left+=200;
                else enemy_rect.left=0;
                for(int i=0;i<enemyCount;i++)
                {
                    
                    enemySprite[i].setTextureRect(enemy_rect);
                    
                }
                pixAntSkin.restart();
            }

            ///////////enemy///////////
            //blood particle//
            if(particle_time.getElapsedTime().asSeconds()>1.0f)
            {
                
                IntRect blRect(0,0,200,200);
                Sprite b_blood(blood_texture,blRect);
                ParticleConstDrop(b_blood,arm1.getPosition());
                int b_blood_alpha=255;
                bloodVecAlpha.push_back(b_blood_alpha);
                bloodVec.push_back(b_blood);
                particle_time.restart();
                
            }
            int bloodCount=bloodVec.size();
            for(int i=0;i<bloodCount;i++)
            {
                bloodVec[i].setColor(Color(0,0,0,bloodVecAlpha[i]));
                bloodVecAlpha[i]-=0.07;
                if(bloodVecAlpha[i]<=10)
                {
                    bloodVec.erase(bloodVec.begin());
                    bloodVecAlpha.erase(bloodVecAlpha.begin());

                }
            }
            for(int i=0;i<bloodCount;i++)
            {
                window.draw(bloodVec[i]);
            }
            
            
        /////////////lengan///////////
        mcHitBox.setPosition(mc.getPosition());
            if(TURN)
            {
                hand.handUpdate(mc,arm1,arm2,window,TURN);
                
            }
            /////////////lengan///////////

            ///Dark///
            dark.setPosition(mc.getPosition());
            dark.setColor(Color(150,150,150));
            dark.setScale(Vector2f(darkScale,darkScale));
            ///Dark///

            player.Update(0,deltaTime);
            mc.setTextureRect(player.plRect);
            
        }
        else////////////MAIN MENU//////////////////
        {
              randBar=rand()%5000;
            if(titleBar.getElapsedTime().asMilliseconds()>=randBar)
            {
                if(randBar%10==0)title_rect.left=710;
                else if(randBar%10==1)title_rect.left=1410;
                else title_rect.left=0;
                title.setTextureRect(title_rect);
                titleBar.restart();
            }
            if(pixAntTimer.getElapsedTime().asSeconds()>2.0f)
            {
                for(int i=0;i<antPxSize;i++)
                {
                    Pix_Arr[i].getPoint();
                }
                pixAntTimer.restart();
            }
            if(pixAntSkin.getElapsedTime().asMilliseconds()>500.0f)
            {
                if(apx_rect.left<912)apx_rect.left+=228;
                else apx_rect.left=0;
                for(int i=0;i<antPxSize;i++)
                {
                    
                    if(!Pix_Arr[i].DEAD)
                    {
                        antPx[i].setTextureRect(apx_rect);
                    }
                    else if(Pix_Arr[i].DEAD)
                    {
                        IntRect rect(0,228,228,217);
                        
                        antPx[i].setTextureRect(rect);
                    }
                }
                pixAntSkin.restart();
            }
            Vector2i mouse_pos;
            bool clicked=false;
            if(Mouse::isButtonPressed(Mouse::Left))
            {
                 mouse_pos= sf::Mouse::getPosition(window); 
                 clicked=true;
            }
            auto translated_pos = window.mapPixelToCoords(mouse_pos); 
            for(int i=0;i<antPxSize;i++)
            {
                Pix_Arr[i].Progress(antPx[i]);
                if((antPx[i].getGlobalBounds().contains(translated_pos))&&clicked)
                {
                    Pix_Arr[i].killed();
                    antPixKilled=true;
                    timer.restart();
                    timeVal=true;
                    clicked=false;
                }
            }
            
            for(int i=0;i<antPxSize;i++)
                {
                    if(antPixKilled)
                    {
                        if(!Pix_Arr[i].DEAD)
                        {
                            antPx[i].setColor(Color(0,0,0,antPxAlpha));
                        }
                    }
                    if(antPxAlpha<10)
                    {
                        if(!Pix_Arr[i].DEAD)
                        {
                            antPx[i].setColor(Color(0,0,0,0));
                           
                        }
                    }

                }
               
            if(antPixKilled)
            {
                antPxAlpha-=0.8; 
                scPxAlpha+=0.1;
                menuMusicVolume-=0.03;
                mainMenuMusic.setVolume(menuMusicVolume);
                if(scPxAlpha>250)scPxAlpha=255;
                screenTransition.setFillColor(Color(0,0,0,scPxAlpha));
            }
            if(menuMusicVolume<10)mainMenuMusic.stop();
        
            if(scPxAlpha>250)
            {
                text2.setColor(Color(255,255,255,255));
            }
            time_interval=timer.getElapsedTime().asSeconds();
          
            if(time_interval>5 && timeVal)
            {
                START=true;
                playStartMusic=true;
                
                scPxAlpha=0;
                antPxAlpha=255;
               
            }
            
            
        }
/////////DRAW///////////
        if(!START)
        {
            for(int i=0;i<antPxSize;i++)
            {
                window.draw(antPx[i]);
            }
            window.draw(title);
            window.draw(text1);
            window.draw(screenTransition);
            window.draw(text2);
         
            window.display();
            window.clear(Color(200,200,200));
        }
        else
        {
        
            for(int i=0;i<enemyCount;i++)
            {
                window.draw(enemySprite[i]);
        
            }
            if(LEVEL==0)window.draw(tutor);
            window.draw(portal);
            window.draw(arm1);
            window.draw(arm2);
            
            window.draw(mc);
            window.draw(dark,BlendMultiply);
 
            if(Trans)
            {
                screenTransition.setFillColor(Color(0,0,0,255));
                window.draw(screenTransition);

            }
            if(GameOver)
            {
                screenTransition.setFillColor(Color(0,0,0,255));
                window.draw(screenTransition);
              
            }
            window.display();
            window.clear(Color(200,200,200));
            
        }
   
    }


    return 0;
}
