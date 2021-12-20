#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include "GraphicsManager.h"
#include "MouvManager.h"
#include "EventsManager.h"

using namespace std;

void jeu(sf::RenderWindow& window, sf::Clock& c, GraphicsManager& gManager, EventsManager& eManager, MouvManager& mManager,int &pause) {
    sf::Event event;
    sf::Time time = c.getElapsedTime();
    
    while (window.pollEvent(event))
    {
        eManager.analyseEvent(&event, &mManager, &window,&pause);
    }
    
    if (pause == 1) {  
        gManager.Render(&window, &mManager, c.getElapsedTime());

        if (time.asSeconds() > 0.2) {
            gManager.destroyed.clear();
        }
        gManager.Delta += time.asMilliseconds() * mManager.speed;

        if (time.asSeconds() > mManager.delta ) {
            c.restart();
            gManager.destroyed=mManager.goDown();
        } 
    }
    else {
        c.restart();

    }

    

}

void menu(sf::RenderWindow& window, sf::Clock& c, GraphicsManager& gManager, EventsManager& eManager, MouvManager& mManager, int& gamestatus, int& menubutton) {
    sf::Event event;
    sf::Time time = c.getElapsedTime();

    while (window.pollEvent(event))
    {
        eManager.MenuEvent(&event,&window,gamestatus,menubutton);
    }

    if (time.asSeconds() > 1) {
        c.restart();
    }


    gManager.RenderMenu(&window,mManager,c,menubutton);
}

int main(){
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Tetris 1942");
    //window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    GraphicsManager gManager;
    EventsManager eManager;
    MouvManager mManager(5,20,10,1);
    
    sf::Texture texture,background,spitfire;
    if (!background.loadFromFile("Img/Background.png"))
        return -1;
    if (!texture.loadFromFile("Img/TextureTetris.png"))
        return -1;
    if (!spitfire.loadFromFile("Img/spitfire.png"))
        return -1;

    sf::Music music;
    if (!music.openFromFile("Music/mainmusic.wav"))
        return -1;
    music.setLoop(1);
    music.setVolume(50);
    music.setPitch(1.1);
    
    gManager.spitfire.setTexture(spitfire);
    gManager.spitfire.setScale(sf::Vector2f(0.3, 0.3));
    gManager.spitfire.setPosition(-100, 50);

    gManager.background.setTexture(background);
    gManager.blockplateau->sprite.setTexture(texture);
    gManager.tetromino->sprite.setTexture(texture);
    gManager.background.setScale(sf::Vector2f(0.5,0.5));
    sf::RectangleShape r(sf::Vector2f(320, 672));
    r.setFillColor(sf::Color(100, 100, 100,150));
    r.setPosition(512, 20);
    gManager.plate = &r;
    
    sf::Clock c;
    int gameStatus(0);
    int menubutton(0);
    int pause = 1;
    while (window.isOpen())
    {   
        if (gameStatus==1 || gameStatus == 2) {
            if(music.getStatus()!=sf::Music::Status::Playing)
                music.play();
            jeu(window, c, gManager, eManager, mManager,pause);
            if (mManager.verifLose()) {
                gameStatus = 0;
                mManager.resetGame(5,20,10);
                music.stop();
            }
            if (pause != 1) {
                music.stop();

            }
        }
        else if (gameStatus == 3) {
            window.close();
        }
        else {        
            menu(window, c, gManager, eManager,mManager, gameStatus,menubutton);
            mManager.mod = menubutton;
        }
    }
    return 0;
}



