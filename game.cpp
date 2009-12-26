#include "game.h"
#include <stdio.h>

// for trace during test , to kept
#include <iostream>
using namespace std;

Game::~Game()
{
    cout << endl; //a cause du compteur de missile, avant de quitter, il faut un seut de ligne
}

void Game::init()
{
    stop=false;
    pause=false;
    passagePause = false;
    GE.init();

    //TODO charger le fichier de niveau et les trajectoire ici

    Mplayer=GE.loadModel("meshes/player.obj","textures/player.png");
    Mboulet=GE.loadModel("meshes/boulet.obj","textures/boulet.png");

    player = ActorPhysique(Mplayer, {0,0,0}, {2,0,0}, {1,1,1});

    timerGenEnemy=INTERVALE_TEMP_ENEMY;
    timerGenShoot=INTERVALE_TEMP_SHOOT;
}

void Game::resize(int width,int heigth)
{
    GE.resize(width,heigth);
}

void Game::update(bool stateKeys[],float time)
{
    this->stateKeys=stateKeys;
    this->time=time;

    //NOTE c'est pas forcément la forme définitive mais ca correspond plus a ce que l'on avais dit.
    if (!pause)
    {
        playerManager();
        firesManager();
        enemiesManager();
        //bonusManager();
        //decorManager();
        collisionManager(); //vérifie les collisions et detruie le vaisseau/missile/bonus si nécéssaire
    }
    gameManager(); // gere le menu, les options graphiques, et les autres trucs

    //Pour le fun
    cout << (char)0x0D <<fires.size()<<" missile(s)  "<<flush;

    render();
}

// fin de l'interface, debut des méthodes privés

void Game::render()
{
    vector<instance> instances;
    instances.push_back(player.getInstance());

    list<Actor>::iterator ite;
    for (ite=enemies.begin(); ite!= enemies.end(); ite++)
    {
        instances.push_back(ite->getInstance());
    }

    list<ActorPhysique>::iterator itf;
    for (itf=fires.begin(); itf!= fires.end(); itf++)
    {
        instances.push_back(itf->getInstance());
    }

    GE.render(instances, {0,0,7,0,0,0,0,1,0},time);
}

/*
*NOTE j'ai fait une version un peu compliqué du déplacement du joueur pour montrer les possibilités de
* ActorPhysique. Cette simulation est physiquement correcte mais ne correpond pas du tout à ce qu'il y'a d'abitude
* dans les jeux. Cependant, je trouve le concept interressant, ça oblige le joueur à mieux anticiper ses
* trajectoires.
*/
void Game::playerManager()
{
    player.setAcceleration( {0,0,0});
    if (stateKeys[T_GAUCHE]) // -x
        player.setAcceleration( {player.getAcceleration().x-5,player.getAcceleration().y,player.getAcceleration().z});
    if (stateKeys[T_DROITE]) // +x
        player.setAcceleration( {player.getAcceleration().x+5,player.getAcceleration().y,player.getAcceleration().z});
    if (stateKeys[T_HAUT]) // +y
        player.setAcceleration( {player.getAcceleration().x,player.getAcceleration().y+5,player.getAcceleration().z});
    if (stateKeys[T_BAS]) // -y
        player.setAcceleration( {player.getAcceleration().x,player.getAcceleration().y-5,player.getAcceleration().z});

    player.update(time);

    if (stateKeys[T_CTRL] and timerGenShoot<=0)
    {
        //on tire 3 missiles
        ActorPhysique fire;
        fire=ActorPhysique(Mboulet, {player.getPosition().x,player.getPosition().y,player.getPosition().z}, {0,0,0}, {0.1,0.1,0.1});
        fire.setVelocity( {player.getVelocity().x+2,player.getVelocity().y-5,player.getVelocity().z});
        fire.setAcceleration( {0,20,0});
        fires.push_back(fire);

        fire=ActorPhysique(Mboulet, {player.getPosition().x,player.getPosition().y,player.getPosition().z}, {0,0,0}, {0.1,0.1,0.1});
        fire.setVelocity( {player.getVelocity().x-2,player.getVelocity().y-5,player.getVelocity().z});
        fire.setAcceleration( {0,20,0});
        fires.push_back(fire);

        fire=ActorPhysique(Mboulet, {player.getPosition().x,player.getPosition().y,player.getPosition().z}, {0,0,0}, {0.1,0.1,0.1});
        fire.setVelocity( {player.getVelocity().x,player.getVelocity().y+10,player.getVelocity().z});
        fire.setAcceleration( {0,0,0});
        fires.push_back(fire);

        timerGenShoot=INTERVALE_TEMP_SHOOT;
    }
    else
        timerGenShoot--;

    player.rotate( {
                       0,0.5,0
                   });

}

void Game::firesManager()
{
    list<ActorPhysique>::iterator it;

    for (it=fires.begin(); it!=fires.end(); it++)
        it->update(time);
}

void Game::enemiesManager()
{
    list<Actor>::iterator it;
    for (it=enemies.begin(); it!=enemies.end(); it++)
        it->update(time);
}

void Game::collisionManager()
{
    //pour l'instant ne sert a virer les objets sortant du cadre
    // si on rentre en collision avec la bordure exterieur on efface l'object

    list<Actor>::iterator ite;
    ite=enemies.begin(); //HACK c'est la chose la plus moche que j'ai jamais faite, mais pour l'instant, j'arrive pas a faire mieux
    while (ite!=enemies.end())
    {
        for (ite=enemies.begin(); ite!=enemies.end() ; ite++)
        {
            if (ite->getPosition().x>4||ite->getPosition().x<-4||ite->getPosition().y>4||ite->getPosition().y<-4)
            {
                enemies.erase(ite);
                break;
            }
        }
    }

    list<ActorPhysique>::iterator itf;
    itf=fires.begin();
    while (itf!=fires.end())
    {
        for (itf=fires.begin(); itf!=fires.end() ; itf++)
        {
            if (itf->getPosition().x>10||itf->getPosition().x<-10||itf->getPosition().y>10||itf->getPosition().y<-10)
            {
                fires.erase(itf);
                break;
            }
        }
    }
}

void Game::gameManager()
{
    // si on est en transition et que la touche pause et relacher, alors fini transition
    if (passagePause && (!stateKeys[T_SPACE])) {
        passagePause = false;
    }
    // si on est pas en transition et que touche pause est appuyer, alors on passe en transition (et en pause ou !pause)
    if (!passagePause && stateKeys[T_SPACE]) {
        pause= (!pause);
        passagePause = true;
    }
    //Si on appuie sur echap, on passe pas par la case menu, on quitte direct
    if (stateKeys[T_ECHAP])
        stop=true;
}
