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
  //  timerGenEnemy = 0;
    addActeur("UFO.obj",0.1,1,1.5); // creation of enemy
  //  timerGenEnemy = 0;
    addActeur("cube.obj");
    timerGenEnemy=INTERVALE_TEMP_ENEMY;
    timerGenShoot=INTERVALE_TEMP_SHOOT;   
}

Game::~Game()
{
}


void Game::manager()
{
    timerGenShoot--;
    timerGenEnemy--;
    if (timerGenEnemy <= 0) {
        addEnemy();
    }
    list<Actor>::iterator it;
    // list<Actor>* enemies = getEnemies();
    for (it=enemies.begin(); it!=enemies.end(); it++)
    {
        (it)->translate(0,-0.001,0); // for each enemy currently
        it->move();
    }
    player.translate(0,-0.001,0);
}

void Game::addTire()
{
    if (timerGenShoot <= 0) {
        addActeur("avion.obj",0.1,getPlayer()->getPosition().x,getPlayer()->getPosition().y,getPlayer()->getPosition().z,0,0,0,0,1,0);
        timerGenShoot=INTERVALE_TEMP_SHOOT;
    }
}

void Game::addEnemy()
{
  QTime time;
    if (timerGenEnemy <= 0) {
         srand( time.elapsed() );
	 float randNumber = rand() / static_cast<float>( RAND_MAX );
	 randNumber = (randNumber-(randNumber/2)); // randomiz posx
        addActeur("cube.obj",0.1,randNumber,1);
        timerGenEnemy=INTERVALE_TEMP_ENEMY;
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


void Game::addActeur(string type, float size, float posx, float posy , float posz, float anglex, float angley, float anglez, float vx, float vy, float vz, float ax, float ay, float az) // parameter for test, to comple
{
    t_position pos = {posx,posy,posz};
    t_rotation rot = {anglex,angley,anglez};
    t_velocity vel = {vx,vy,vz};
    t_accel accel = {ax,ay,az};
    Actor actor = Actor(getModel(type),size,pos,rot,vel,accel);
    enemies.push_back(actor); // add this actor in list enemies
}


void Game::addModel(string type)
{
    Model3D model3D = Model3D(); //Model3D(type);
    models.insert( pair<string,Model3D>(type,(Model3D)model3D) );
}
