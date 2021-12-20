#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

#include "GraphicsManager.h"
#include "MouvManager.h"
#include <iostream>
#include "Block.h"


GraphicsManager::GraphicsManager() {
    tetromino = new Block();
    blockplateau = new Block();
    Delta = 0;
};


int GraphicsManager::Render(sf::RenderWindow* window,MouvManager* mManager,sf::Time time) {
    window->clear();
    window->draw(background);
    
    sf::RectangleShape test(sf::Vector2f(320, 32));
    if (Delta >= 0.3) {
        spitfire.move(sf::Vector2f(2, -0.3));       
        Delta = 0;
    }
    if (spitfire.getPosition().x > 1500) {
        spitfire.setPosition(-100, 50);
    }
    window->draw(spitfire);

    window->draw(*plate);
    tetromino->setX(mManager->currentPiece->mid);
    tetromino->changeTexture(mManager->currentPiece->color);
    sf::RectangleShape ghostrec(sf::Vector2f(32, 32));
    ghostrec.setOutlineColor(sf::Color::White);

    for (int x=0; x < mManager->plateau->nbLine ; ++x) {
        for (int y=0; y < mManager->plateau->nbCol ; ++y) {
            if (mManager->plateau->plateau[x][y] !=0) {
                blockplateau->changeTexture(mManager->plateau->plateau[x][y]);
                blockplateau->setX(512 + y * Block::TEXTURE_SIZE);
                blockplateau->setY(50 + x * Block::TEXTURE_SIZE);
                window->draw(blockplateau->sprite);
            }
        }
    }
    for (int i : destroyed) {
        for (int y = 0; y < mManager->plateau->nbCol; ++y) {
            ghostrec.setPosition(sf::Vector2f(512 + y * Block::TEXTURE_SIZE, 50 + i * Block::TEXTURE_SIZE));
            window->draw(ghostrec);
        }
    }

    sf::Font font;
    if (!font.loadFromFile("Font/stocky.ttf"))
    {
        return 0;
    }
    sf::Text text("Score " + to_string(mManager->points),font,30);


    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);
    text.setPosition(250, 600);
    window->draw(text);
    text.setString(to_string(mManager->level));
    text.setPosition(250, 500);
    text.setCharacterSize(80);
    window->draw(text);

    sf::RectangleShape r(sf::Vector2f(192,128));
    r.setFillColor(sf::Color(100, 100, 100, 150));
    r.setPosition(286, 68);
    window->draw(r);

    for (int* i : mManager->currentPiece->compoPiece) {
        tetromino->setX(512 + i[0] * Block::TEXTURE_SIZE);
        tetromino->setY(50 + ((i[1]-1+ time.asSeconds()*(mManager->speed)) * Block::TEXTURE_SIZE));
        window->draw(tetromino->sprite);
    } 


    Piece ghostpiece = *mManager->currentPiece;
    while (down(mManager->plateau,&ghostpiece))
        ghostpiece.goDown();
    
    
    ghostrec.setFillColor(sf::Color::Transparent );
    ghostrec.setOutlineThickness(1);

    for (int* i : ghostpiece.compoPiece) {
        ghostrec.setPosition(sf::Vector2f(512 + i[0] * Block::TEXTURE_SIZE, 50 + (i[1] * Block::TEXTURE_SIZE)));
        window->draw(ghostrec);
    }

    for (int* i : mManager->nextPiece->compoPiece) {
        blockplateau->changeTexture(mManager->nextPiece->color);
        if (mManager->nextPiece->piece == 3) {
            blockplateau->setX(222 + i[0] * Block::TEXTURE_SIZE);
            blockplateau->setY(120 + i[1] * Block::TEXTURE_SIZE);
        }
        else if (mManager->nextPiece->piece == 4) {
            blockplateau->setX(190 + i[0] * Block::TEXTURE_SIZE);
            blockplateau->setY(100 + i[1] * Block::TEXTURE_SIZE);
        }else{

            blockplateau->setX(205 + i[0] * Block::TEXTURE_SIZE);
            blockplateau->setY(100 + i[1] * Block::TEXTURE_SIZE);
        }

        window->draw(blockplateau->sprite);
    }
    

    window->display();
    return 1;
};

int GraphicsManager::RenderMenu(sf::RenderWindow* window,MouvManager &mManager,sf::Clock &c,int& menubutton) {
    sf::Text text;
    sf::Font font;
    vector<string> list = { "Jouer Tetris","Jouer Tetris 1942","Quitter" };

    if (!font.loadFromFile("Font/stocky.ttf"))
    {
        return 0;
    }
    
    window->clear();    
    window->draw(background);

    sf::Color color(100, 100, 100,150);

    sf::RectangleShape r(sf::Vector2f(275, 300));
    r.setFillColor(color);
    r.setPosition(40, 120);
    window->draw(r);
    text.setFont(font);
    text.setPosition(45, 125);
    text.setCharacterSize(15);
    text.setString("   Controles  \n\n QD Gauche droite\n Z Rotation\n S Accelerer\n ESPACE Descendre pièce\n P Pause");
    window->draw(text);




    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);

    if (menubutton == 1) {
        text.setString("Les dynamites et barils radioactifs, offrent des bonus!!");
        text.setPosition(340, 420);
        text.setCharacterSize(20);

        window->draw(text);

    }

    

    for (int i = 0; i < 3; ++i) {
        
        text.setFillColor(sf::Color::White);
        
        text.setCharacterSize(50);

        text.setString(list[i]);
        text.setPosition(350, i * 150 + 180);
        if (i == menubutton && c.getElapsedTime().asMilliseconds() < 500) {
                text.setFillColor(color);
        }
        window->draw(text);
        
    }
    text.setFillColor(sf::Color::White);

    if (mManager.maxScore != 0) {
        text.setPosition(800, 200);
        text.setCharacterSize(20);

        text.setRotation(20);
        text.setString("Meilleur Score "+to_string(mManager.maxScore));
        window->draw(text);
    }
    
    window->display();
    return 1;
};