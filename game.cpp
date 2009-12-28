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
    resetCam();


    GE.init();

    //TODO charger le fichier de niveau et les trajectoire ici

    Mplayer=GE.loadModel("meshes/player.obj","textures/player.png");
    Mboulet=GE.loadModel("meshes/boulet.obj","textures/boulet.png");

    player = ActorPhysique(Mplayer, {0,0,0}, {0,0,0}, {1,1,1});

    timerGenEnemy=INTERVALE_TEMP_ENEMY;
    timerGenShoot=INTERVALE_TEMP_SHOOT;
}

void Game::resize(int width,int heigth)
{
    GE.resize(width,heigth);
}

void Game::update(bool stateKeys[], bool stateButtons[], QPoint deltaMouse, int deltaWheel,float time, int width, int height) // NOTE peut etre passer un pointeur sur kb et mouse !
{
    this->stateKeys=stateKeys;
    this->stateButtons=stateButtons;
    this->deltaMouse=deltaMouse;
    this->deltaWheel=deltaWheel;
    this->time=time;
    this->widthView=width;
    this->heightView=height;
    this->width=3;
    this->height=3;

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
    if (pause)
        pauseManager();

    //Pour le fun
    cout << (char)0x0D <<fires.size()<<" missile(s)  et delta wheel : " << deltaWheel << flush;

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
    GE.render(instances, {-sin(longitude)*cos(latitude)*zoom,sin(latitude)*zoom,cos(longitude)*cos(latitude)*zoom,centerX,centerY,0,0,1,0} , {0.5,0.5,0.5,{0.05,0.05,0.05,1},{0.4,0.4,0.3,1},{0.9,0.8,0.8,1}},time);
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
    if (stateKeys[K_LEFT]) // -x
        player.setAcceleration( {player.getAcceleration().x-5,player.getAcceleration().y,player.getAcceleration().z});
    if (stateKeys[K_RIGHT]) // +x
        player.setAcceleration( {player.getAcceleration().x+5,player.getAcceleration().y,player.getAcceleration().z});
    if (stateKeys[K_UP]) // +y
        player.setAcceleration( {player.getAcceleration().x,player.getAcceleration().y+5,player.getAcceleration().z});
    if (stateKeys[K_DOWN]) // -y
        player.setAcceleration( {player.getAcceleration().x,player.getAcceleration().y-5,player.getAcceleration().z});

    player.update(time);

    if ((((stateKeys[K_CTRL]) || (stateButtons[B_LEFT])) and timerGenShoot<=0))
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
    //NOTE Pourquoi (paul) as tu mis une bouche while autour du for ? je comprend vraiment pas !
    //NOTE C'est pas si horrible (sans le while) tu parcour toute les enemi (et fires) en verifiant s'il sont hors jeu our pas !
//     while (ite!=enemies.end())
//     {
    for (ite=enemies.begin(); ite!=enemies.end() ; ite++)
    {
        if (ite->getPosition().x>4||ite->getPosition().x<-4||ite->getPosition().y>4||ite->getPosition().y<-4)
        {
            enemies.erase(ite);
            break;
        }
    }
//     }

    list<ActorPhysique>::iterator itf;
    itf=fires.begin();
//     while (itf!=fires.end())
//     {
    for (itf=fires.begin(); itf!=fires.end() ; itf++)
    {
        if (itf->getPosition().x>10||itf->getPosition().x<-10||itf->getPosition().y>10||itf->getPosition().y<-10)
        {
            fires.erase(itf);
            break;
        }
    }
//     }
    // TODO ameliorer definition des bords
    //verification des bords verticaux ensuite des bords horizontaux. (evite de sortir sur les coins.)
    if (player.getPosition().x<-width)
    {
        player.setVelocity( {-player.getVelocity().x*0.2,player.getVelocity().y,player.getVelocity().z});
    }
    else if (player.getPosition().x>width)
    {
        player.setVelocity( {-player.getVelocity().x*0.2,player.getVelocity().y,player.getVelocity().z});
    }

    if (player.getPosition().y<-height-1)
    {
        player.setVelocity( {player.getVelocity().x,-player.getVelocity().y*0.2,player.getVelocity().z});
    }

    else if (player.getPosition().y>height-2)
    {
        player.setVelocity( {player.getVelocity().x,-player.getVelocity().y*0.2,player.getVelocity().z});
    }
}

void Game::gameManager()
{
    // Si on est en transition et que la touche pause est relaché, alors fini transition
    if (passagePause && (!stateKeys[K_SPACE])) {
        passagePause = false;
        pause= (!pause); // seulement une fois que la transition est fini, on change l'etat.
    }
    // Si on est pas en transition et que touche pause est appuyé, alors on passe en transition (et en pause ou !pause)
    if (!passagePause && stateKeys[K_SPACE]) {
        if (pause == true)
        {
            resetCam();
        }
        passagePause = true;
    }
    //Si on appuie sur echap, on passe pas par la case menu, on quitte direct
    if (stateKeys[K_ESC])
        stop=true;
}

// Lors du zoom ou des translation, c'est la camera qui bouge, lors des rotation, c'est la scene.
//NOTE Toute les valeur ici sont prisent "au hasard" (0.05,0.02 ...) peut etre trouver des relation avec des nombre representant quelques choses pour nous !?
void Game::pauseManager() // TODO acceleration, reset camera "avec douceur"
{

    if (stateKeys[K_CTRL]) {
        if (stateKeys[K_UP]) {
            zoom -= 0.05;
        }
        else if (stateKeys[K_DOWN]) {
            zoom += 0.05;
        }
        else if ((stateKeys[K_LEFT]) && (stateKeys[K_RIGHT])) {
            resetCam();
        }
    }

    else if (stateKeys[K_SHIFT]) {
        if (stateKeys[K_UP]) {
            centerY += 0.05;
        }
        else if  (stateKeys[K_DOWN]) {
            centerY -= 0.05;
        }
        if (stateKeys[K_LEFT]) {
            centerX -= 0.05;
        }
        else if (stateKeys[K_RIGHT]) {
            centerX += 0.05;
        }
        if ((zoom >= ZOOM_MIN) and (deltaWheel > 0)) {
            zoom +=(-deltaWheel/(float)240);
            if (zoom<ZOOM_MIN)
                zoom = ZOOM_MIN;
        }
        else if ((zoom <= ZOOM_MAX) and (deltaWheel < 0)) {
            zoom +=(-deltaWheel/(float)240);
            if (zoom>ZOOM_MAX)
                zoom =ZOOM_MAX;
        }
    }

    else {
        //>=2 ou <= -2 pour la sensibiliter -> en 20ms, la souris a parcouru plus de 2 ou moin de -2 pixels (Delta).
        if ((stateButtons[B_LEFT]) && ((deltaMouse.y() >= 2 || deltaMouse.y() <= -2))) {
            centerY +=deltaMouse.y()*0.02;
        }
        if ((stateButtons[B_LEFT]) && ((deltaMouse.x() >= 2 || deltaMouse.x() <= -2))) {
            centerX +=-deltaMouse.x()*0.02;
        }
        if ((stateButtons[B_MIDLE]) && ((deltaMouse.y() >= 2 || deltaMouse.y() <= -2))) {
            latitude+=0.01*deltaMouse.y();
        }
        if ((stateButtons[B_MIDLE]) && ((deltaMouse.x() >= 2 || deltaMouse.x() <= -2))) {
            longitude+=0.01*deltaMouse.x();
        }
        if ((zoom >= ZOOM_MIN) and (deltaWheel > 0)) {
            zoom +=(-deltaWheel/(float)60);
            if (zoom<ZOOM_MIN)
                zoom = ZOOM_MIN;
        }
        else if ((zoom <= ZOOM_MAX) and (deltaWheel < 0)) {
            zoom +=(-deltaWheel/(float)60);
            if (zoom>ZOOM_MAX)
                zoom =ZOOM_MAX;
        }
        if (stateKeys[K_UP])
            latitude+=0.02;
        if (stateKeys[K_DOWN])
            latitude-=0.02;
        if (stateKeys[K_LEFT])
            longitude-=0.02;
        if (stateKeys[K_RIGHT])
            longitude+=0.02;
    }
    if (latitude >3.1415/2)
        latitude=3.1415/2;
    if (latitude < -3.1415/2)
        latitude=-3.1415/2;
}
