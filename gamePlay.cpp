#include "gamePlay.h"
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <sstream>

/* le plan de jeu ce fait sur xz */

//     Y--------X
//     |
//     |
//     |
//     Z

// for trace during test , to kept
#include <iostream>
using namespace std;




GamePlay::~GamePlay()
{
    cout << endl; //a cause du compteur de missile, avant de quitter, il faut un seut de ligne
}

void GamePlay::init(Models* models, Etat* etatGame)
{

    this->etatGame = etatGame;
    this->scoreValeur = 0;
    this->models = models;


    player = ActorPlayer(models->getMplayer(), {0,0,0}, {0,-90,0}, {1,1,1}, 2, 10/3);
    score = Chiffre(scoreValeur, {-12,0,-10}, {0,0,0}, {1.2,1.2,.5}, 0.7, models->getMChiffres()); // test des chiffres
    leScore = Text("ab c2z3dea", {-12,0,-11}, {0,0,0}, {1.2,1.2,.5}, 0.7, models->getMChiffres(),models->getMLettersa()); // test du text, pour l'instant "abcde"

    timerGenEnemy=INTERVALE_TEMP_ENEMY;
    timerGenShoot=INTERVALE_TEMP_SHOOT;
    timerGenShootGros=INTERVALE_TEMP_SHOOT_GROS;
}


void GamePlay::gameManager(bool stateKeys[], bool stateButtons[], Point deltaMouse, int deltaWheel,float time, int width, int height) // NOTE peut etre passer un pointeur sur kb et mouse !
{
    this->stateKeys=stateKeys;
    this->stateButtons=stateButtons;
    this->deltaMouse=deltaMouse;
    this->deltaWheel=deltaWheel;
    this->dTime=time;
    this->widthView=width;
    this->heightView=height;
    this->width=NB_UNITY_WIDTH;
    this->height=NB_UNITY_HEIGHT;

    playerManager();
    firesManager();
    enemiesManager();
    //bonusManager();
    //decorManager();
    collisionManager(); //vérifie les collisions et detruie le vaisseau/missile/bonus si nécéssaire


    //Pour le fun
    cout << (char)0x0D << friendFires.size() +  enemiesFires.size()<<" missile(s) " << flush;

}


void GamePlay::getRender(vector<instance>* instances) {

    // on recupere toute les instances a afficher
    vector<Actor> text;
    vector<Actor>::iterator itA;
    list<ActorPhysique>::iterator itAP;

    instances->push_back(player.getInstance());
    for (itAP=enemies.begin(); itAP!= enemies.end(); itAP++) {
        instances->push_back(itAP->getInstance());
    }
    for (itAP=enemiesFires.begin(); itAP!= enemiesFires.end(); itAP++) {
        instances->push_back(itAP->getInstance());
    }
    for (itAP=friendFires.begin(); itAP!= friendFires.end(); itAP++) {
        instances->push_back(itAP->getInstance());
    }

    text = score.getText();
    for (itA=text.begin(); itA!=text.end(); itA++) {
        instances->push_back(itA->getInstance());
    }
    text = leScore.getText();
    for (itA=text.begin(); itA!=text.end(); itA++) {
        instances->push_back(itA->getInstance());
    }
}
/*
*NOTE j'ai fait une version un peu compliqué du déplacement du joueur pour montrer les possibilités de
* ActorPhysique. Cette simulation est physiquement correcte mais ne correpond pas du tout à ce qu'il y'a d'abitude
* dans les jeux. Cependant, je trouve le concept interressant, ça oblige le joueur à mieux anticiper ses
* trajectoires.
*/
void GamePlay::playerManager()
{
    player.setAcceleration( {0,0,0});
    if (stateKeys[K_LEFT]) // -x
        player.setAcceleration( {player.getAcceleration().x-10,player.getAcceleration().y,player.getAcceleration().z});
    if (stateKeys[K_RIGHT]) // +x
        player.setAcceleration( {player.getAcceleration().x+10,player.getAcceleration().y,player.getAcceleration().z});
    if (stateKeys[K_UP]) // +y
        player.setAcceleration( {player.getAcceleration().x,player.getAcceleration().y,player.getAcceleration().z-20});
    if (stateKeys[K_DOWN]) // -y
        player.setAcceleration( {player.getAcceleration().x,player.getAcceleration().y,player.getAcceleration().z+20});

    player.update(dTime);
    // TODO ameliorer definition des bords

    if ((((stateKeys[K_TIR]) || (stateButtons[B_LEFT])) and timerGenShoot<=0))
    {
        ActorPhysique fire;
        fire=ActorPhysique(models->getMboulet(), {player.getPosition().x,player.getPosition().y,player.getPosition().z}, {0,0,0}, {0.05,0.05,0.05});
        fire.setVelocity( {player.getVelocity().x/3+random(-0.5,0.5),player.getVelocity().y/3,player.getVelocity().z/3-random(15,18)});
        fire.setAcceleration( {0,0,0});
        friendFires.push_back(fire);

        timerGenShoot=INTERVALE_TEMP_SHOOT;
        scoreValeur++; // rien a faire la, mais c'est pour tester
    }
    if ((((stateKeys[K_TIR_SECOND]) || (stateButtons[B_RIGHT])) and timerGenShootGros<=0))
    {
        ActorPhysique fire;
        for (float f =-0.8;f<=0.8;f+=0.2)
        {
            if (random(0,1) < 0.9) {
                fire=ActorPhysique(models->getMboulet(), {player.getPosition().x+0.3,player.getPosition().y,player.getPosition().z+f}, {0,0,0}, {0.05,0.05,0.05});
                fire.setVelocity( {player.getVelocity().x/3+random(15,18),player.getVelocity().y/3,player.getVelocity().z/5+random(-0.5,0.5)});
                friendFires.push_back(fire);
            }
            if (random(0,1) < 0.9) {
                fire=ActorPhysique(models->getMboulet(), {player.getPosition().x-0.3,player.getPosition().y,player.getPosition().z+f}, {0,0,0}, {0.05,0.05,0.05});
                fire.setVelocity( {player.getVelocity().x/3-random(15,18),player.getVelocity().y/3,player.getVelocity().z/5+random(-0.5,0.5)});
                friendFires.push_back(fire);
            }
        }
        timerGenShootGros=INTERVALE_TEMP_SHOOT_GROS;
    }
    else {
        timerGenShoot--;
        timerGenShootGros--;
    }
    score.update(scoreValeur,.7, models->MChiffres);
}

void GamePlay::firesManager()
{
    list<ActorPhysique>::iterator it;

    for (it=friendFires.begin(); it!=friendFires.end(); it++) {
        it->update(dTime);
    }
    for (it=enemiesFires.begin(); it!=enemiesFires.end(); it++) {
        it->update(dTime);
    }
}

void GamePlay::enemiesManager()
{
    list<ActorPhysique>::iterator it;
    for (it=enemies.begin(); it!=enemies.end(); it++) {
        it->update(dTime);
    }
}

void GamePlay::collisionManager()
{
    //pour l'instant ne sert a virer les objets sortant du cadre
    // si on rentre en collision avec la bordure exterieur on efface l'object
    player.colisionBord(width,height); // donner une leger rotation au vaisseau

    list<ActorPhysique>::iterator itAP;
    for (itAP=enemies.begin(); itAP!=enemies.end() ; itAP++) {
        if (itAP-> sortieEcran(width+5,height+5))
        {
            enemies.erase(itAP);
            break;
        }
    }
    for (itAP=friendFires.begin(); itAP!=friendFires.end() ; itAP++)
    {
        if (itAP-> sortieEcran(width+5,height+5))
        {
            friendFires.erase(itAP);
            break;
        }
    }
    for (itAP=enemiesFires.begin(); itAP!=enemiesFires.end() ; itAP++)
    {
        if (itAP-> sortieEcran(width+5,height+5))
        {
            enemiesFires.erase(itAP);
            break;
        }
    }
}
