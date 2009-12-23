#include <QtGui>
#include "game.h"
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
    addModel("bouler.obj");

    player = Actor(getModel("demon.obj")); // creation of player
  //  timerGenEnemy = 0;
    addActor("UFO.obj",0.1,1,1.5); // creation of enemy
  //  timerGenEnemy = 0;
    addActor("cube.obj");
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
        addActor("bouler.obj",TAILLE_BOULET,getPlayer()->getPosition().x,getPlayer()->getPosition().y,getPlayer()->getPosition().z,0,0,0,0,VELOCITY_BOULET,0);
        timerGenShoot=INTERVALE_TEMP_SHOOT; // we can regenerate tire before this val is > 0
    }
}

void Game::addEnemy()
{

    if (timerGenEnemy <= 0) {
        float randX = random(-1.0,1.0); // where actor will be in X
	float randE = random(0.0,1.0); // if RandE pair then demon else cube

	if (isPair(randE))
	  addActor("demon.obj",0.08,randX,1);
	else
	  addActor("cube.obj",0.1,randX,1);  
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


void Game::addActor(string type, float size, float posx, float posy , float posz, float anglex, float angley, float anglez, float vx, float vy, float vz, float ax, float ay, float az) // parameter for test, to comple
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
