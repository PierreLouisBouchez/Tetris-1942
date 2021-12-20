#include <SFML/Graphics.hpp>
#include "EventsManager.h"
#include "MouvManager.h"
#include <iostream>
#include "Block.h"



void EventsManager::analyseEvent(sf::Event* event,MouvManager* mManager, sf::RenderWindow* window, int *pause) {
    switch (event->type)
    {

        case sf::Event::Resized:
            window->setSize(sf::Vector2u(window->getSize().x, window->getSize().x * 0.5625));

            break;
        case sf::Event::Closed:
            window->close();
            break;

            // touche pressée
        case sf::Event::KeyPressed:
            switch (event->key.code) {
            case sf::Keyboard::D:
                mManager->goRight();
                break;
            case sf::Keyboard::Q:
                mManager->goLeft();
                break;
            case sf::Keyboard::Z:
                mManager->turnLeft();
                break;
            case sf::Keyboard::S:
                mManager->goDown();
                break;
            case sf::Keyboard::Right:
                mManager->goRight();
                break;
            case sf::Keyboard::Left:
                mManager->goLeft();
                break;
            case sf::Keyboard::Up:
                mManager->turnLeft();
                break;
            case sf::Keyboard::Down:
                mManager->goDown();
                break;
            case sf::Keyboard::P:
                *pause = *pause * -1;
                break;
            case sf::Keyboard::Space:
                while (down(mManager->plateau, mManager->currentPiece))
                    mManager->goDown();
                break;
            default:
                break;
            }
            break;

        default:
            break;
    }
}


void EventsManager::MenuEvent(sf::Event* event, sf::RenderWindow* window,int &gamestatus, int& menubutton) {

    switch (event->type)
    {
    case sf::Event::Resized:
        window->setSize(sf::Vector2u(window->getSize().x, window->getSize().x * 0.5625));

        break;
    case sf::Event::Closed:
        window->close();
        break;
        // touche pressée
    case sf::Event::KeyPressed:
        switch (event->key.code) {
        case sf::Keyboard::Enter:
            gamestatus = menubutton + 1;
            break;
        case sf::Keyboard::Space:
            gamestatus = menubutton + 1;
            break;
        case sf::Keyboard::Z:
            menubutton--;
            break;
        case sf::Keyboard::S:
            menubutton++;
            break;
        case sf::Keyboard::Up:
            menubutton--;
            break;
        case sf::Keyboard::Down:
            menubutton++;
            break;
        default:
            break;
        }    
        
    default:
        break;
    }
    if (menubutton == -1) {
        menubutton = 2;
    }
    if (menubutton == 3) {
        menubutton = 0;
    }
}
