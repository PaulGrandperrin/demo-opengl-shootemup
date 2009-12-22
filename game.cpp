#include <QtGui>
#include "game.h"
#include <iostream>
#include <stdio.h>

// for trace during test , to kept
#include <iostream>
using namespace std;

Game::Game()
{
    addModel("cube.obj"); // creation of Model for actor
    addModel("demon.obj");
    addModel("cow.obj");
    addModel("UFO.obj");
    addModel("tire2.obj");
    addModel("avion.obj");

    player = Actor(getModel("demon.obj")); // creation of player
    addActeur("UFO.obj",1,1.5); // creation of enemy
    addActeur("cube.obj");
}

Game::~Game()
{
}


void Game::manager()
{

    list<Actor>::iterator it;
    // list<Actor>* enemies = getEnemies();
    for (it=enemies.begin(); it!=enemies.end(); it++)
    {
        (it)->scale(0.0005); // for each enemy currently
    }
}



void Game::display()
{
    player.display();
    //  list<Actor>* enemies = getEnemies();
    list<Actor>::iterator it;
    for (it=enemies.begin(); it!= enemies.end(); it++)
    {
        it->display(); // display each ennemy
    }
}


Model3D* Game::getModel(string type)
{
    return &(models.find(type)->second); // the second is one model3D
}


void Game::addActeur(string type, float posx, float posy , float posz) // parameter for test, to complet
{
    Actor acteur = Actor(getModel(type),posx,posy,posz);
    enemies.push_back(acteur); // add this actor in list enemies
}


void Game::addModel(string type)
{
    Model3D model3D = Model3D(); //Model3D(type);
    models.insert( pair<string,Model3D>(type,(Model3D)model3D) );
}
