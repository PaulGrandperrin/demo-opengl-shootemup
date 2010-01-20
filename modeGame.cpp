#include "modeGame.h"
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




ModeGame::~ModeGame()
{
    cout << endl; //a cause du compteur de missile, avant de quitter, il faut un seut de ligne
}

void ModeGame::init(Models* models, Etat* etatGame)
{
    Mode::init(models, etatGame);

    vect pPlayer={0,0,0}, rPlayer= {0,-90,0}, sPlayer={1,1,1};
    player = ActorPlayer(models->getMplayer(), pPlayer, rPlayer, sPlayer);
    
    vect pScore={-12.5,0,-11}, rScore= {0,0,0}, sScore={1,1,0.5};
    score = Score(models->getMChiffres(), 0, pScore, rScore, sScore, 0.6, LEFT); // test des chiffres
    
    vect pText={-12.5,0,-12}, rText= {0,0,0}, sText={0.8,0.8,0.5};
    leScore = Text(models->getMChiffres(),models->getMLettersM(), "Le Score du Player :", pText, rText, sText, 0.6, LEFT); // test du text, pour l'instant "abcde"

    timerGenEnemy=INTERVALE_TEMP_ENEMY;
    timerGenShoot=INTERVALE_TEMP_SHOOT;
    timerGenShootGros=INTERVALE_TEMP_SHOOT_GROS;
}


void ModeGame::gameManager(bool stateKeys[], bool stateButtons[], Point deltaMouse, int deltaWheel,float time, int width, int height) // NOTE peut etre passer un pointeur sur kb et mouse !
{
    Mode::Manager(stateKeys, stateButtons, deltaMouse, deltaWheel, time, width, height);

    playerManager();
    firesManager();
    enemiesManager();
    //bonusManager();
    //decorManager();
    collisionManager(); //vérifie les collisions et detruie le vaisseau/missile/bonus si nécéssaire


    //Pour le fun
    cout << (char)0x0D << friendFires.size() +  enemiesFires.size()<<" missile(s) " << flush;

}


void ModeGame::getRender(vector<instance>* instances) {

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

    if (*etatGame == GAME) {
        // on affiche le score ..., et autre info
        text = score.getText();
        for (itA=text.begin(); itA!=text.end(); itA++) {
            instances->push_back(itA->getInstance());
        }
        text = leScore.getText();
        for (itA=text.begin(); itA!=text.end(); itA++) {
            instances->push_back(itA->getInstance());
        }
    }
}
/*
*NOTE j'ai fait une version un peu compliqué du déplacement du joueur pour montrer les possibilités de
* ActorPhysique. Cette simulation est physiquement correcte mais ne correpond pas du tout à ce qu'il y'a d'abitude
* dans les jeux. Cependant, je trouve le concept interressant, ça oblige le joueur à mieux anticiper ses
* trajectoires.
*/
void ModeGame::playerManager()
{
//     player.setAcceleration( {0,0,0});
    vect accl={0,0,0};
    if (stateKeys[K_LEFT]) // -x
	accl.x-=10;
        player.setAcceleration( accl );
    if (stateKeys[K_RIGHT]) // +x
	accl.x+=10;
        player.setAcceleration( accl);
    if (stateKeys[K_UP]) // +y
	accl.z-=20;
        player.setAcceleration( accl);
    if (stateKeys[K_DOWN]) // -y
      	accl.z+=20;
        player.setAcceleration( accl);

    player.update(dTime);
    // TODO ameliorer definition des bords

    vect p={player.getPosition().x,player.getPosition().y,player.getPosition().z}, r={0,0,0}, s={0.1,0.1,0.1};
    vect pLeft={player.getPosition().x-0.3,player.getPosition().y,player.getPosition().z};
    vect pRight={player.getPosition().x+0.3,player.getPosition().y,player.getPosition().z};
    vect vel={player.getVelocity().x/3,player.getVelocity().y/3,player.getVelocity().z/3};
    
    if ((((stateKeys[K_TIR]) || (stateButtons[B_LEFT])) and timerGenShoot<=0))
    {
        ActorPhysique fire;
	vel.x += random(-0.5,0.5);
	vel.z -= random(15,18);
        fire=ActorPhysique(models->getMboulet(), p, r, s);
        fire.setVelocity( vel );
        friendFires.push_back(fire);

        timerGenShoot=INTERVALE_TEMP_SHOOT;
        score.setScore(models->getMChiffres(), 1); // rien a faire la, mais c'est pour tester
    }
    if ((((stateKeys[K_TIR_SECOND]) || (stateButtons[B_RIGHT])) and timerGenShootGros<=0))
    {
        ActorPhysique fire;
	int iScore=0;
        for (float f =-0.8;f<=0.8;f+=0.2)
        {
            if (random(0,1) < 0.9) {
		vel.x = 0; vel.z = 0;
// 	        pRight.x=player.getPosition().x+0.3;
		pRight.z=player.getPosition().z+f;
		vel.x += random(15,18);
		vel.z += random(-0.5,0.5);
                fire=ActorPhysique(models->getMboulet(), pRight, r, s);
                fire.setVelocity( vel);
                friendFires.push_back(fire);
		iScore++;
            }
            if (random(0,1) < 0.9) {
		vel.x = 0; vel.z = 0;
// 	        pLeft.x=player.getPosition().x+0.3;
		pLeft.z=player.getPosition().z+f;
		vel.x -= random(15,18);
		vel.z += random(-0.5,0.5);
                fire=ActorPhysique(models->getMboulet(),pLeft, r, s);
                fire.setVelocity( vel);
                friendFires.push_back(fire);
		iScore++;
            }
        }
        timerGenShootGros=INTERVALE_TEMP_SHOOT_GROS;
	score.setScore(models->getMChiffres(), iScore); // rien a faire la, mais c'est pour tester
    }
    else {
        timerGenShoot--;
        timerGenShootGros--;
    }
}

void ModeGame::firesManager()
{
    list<ActorPhysique>::iterator it;

    for (it=friendFires.begin(); it!=friendFires.end(); it++) {
        it->update(dTime);
    }
    for (it=enemiesFires.begin(); it!=enemiesFires.end(); it++) {
        it->update(dTime);
    }
}

void ModeGame::enemiesManager()
{
    list<ActorPhysique>::iterator it;
    for (it=enemies.begin(); it!=enemies.end(); it++) {
        it->update(dTime);
    }
}

void ModeGame::collisionManager()
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
