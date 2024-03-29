#include "./modeGame.h"
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <sstream>
extern Parameters *parametre;

/* le plan de jeu ce fait sur xz */

//     Y--------X
//     |
//     |
//     |
//     Z

// for trace during test , to kept
#include <iostream>
using namespace std;
extern Parameters *parametre;



ModeGame::~ModeGame()
{
}

ModeGame::ModeGame(Models* models, Camera* camera, Etat* etatGame, SwitchEtat* switchMode,SoundEngine* SE) : Mode(models, camera, etatGame, switchMode,SE)
{
    // si on reconstruit le modeGame, se n'est pas la fin !!
    end = false;
    toEnd = false;
    playerHeart = 0;


    // on vide les vecteur d'ennemi... pour la prochaine partie
    friendFires.clear();
    enemiesFires.clear();
    trajectories.clear();
    timersGenEnemy.clear();
    
    int intHealth = 0;

    if (parametre->getdif() == 2)
	intHealth = HEALTH_PLAYER_HARD;
    else
	intHealth = HEALTH_PLAYER_EASY;

    timerGenEnemy=INTERVALE_TEMP_ENEMY;
    timerGenShoot=INTERVALE_TEMP_SHOOT;
    timerGenShootGros=INTERVALE_TEMP_SHOOT_GROS;
    timerGenTrajectorySequence = INTERVALE_TEMP_TRAJECTORY_SEQUENCE;
    timerFin=INTERVALE_TEMP_FIN;

    // on reconstruit tout les objets
    vect pPlayer={0,0,0}, rPlayer= {0,-90,0}, sPlayer={1,1,1};
    player = ActorPlayer(models->getMplayer(), pPlayer, rPlayer, sPlayer, intHealth ,0.4);

    vect pScore={-12,0,-10}, rScore= {0,0,0}, sScore={1,1,0.5};
    score = Score(models, 0, "Score:", pScore, rScore, sScore, 0.6, LEFT); // test des chiffres

    vect pVie={12,0,-10}, rVie= {0,0,0}, sVie={1,1,0.5};
    health = Health(models, intHealth, "Health:" , pVie, rVie, sVie, 0.6, RIGHT); // test des chiffres

    vect pEnd={0,0,0}, rEnd= {0,0,0}, sEnd={2,2,1};

    tEndDead = Text(models, "Oh, you died !", pEnd, rEnd, sEnd, 0.6, CENTER); // test du text, pour l'instant "abcde"
    tEndWin = Text(models, "Nice, you won !", pEnd, rEnd, sEnd, 0.6, CENTER); // test du text, pour l'instant "abcde"

    // Chargement des trajectoires
    TrajectoryFile tFile("levels/traj_lvl_default.data");
    if (!tFile.isEnded()) {
        tFile.read(trajectories); // On charge les trajectoires dans trajectories
    } else {
        cout << "Trajectory file not found !" << endl;
        exit(0);
    }

    // On initialise les timers de generation d'ennemi à TIMER_OFF pour dire qu'ils sont désactivés au début
    int traj_list_size = trajectories.size();
    for (int i=0; i<traj_list_size; i++)
        timersGenEnemy.push_back(TIMER_OFF);
}

void ModeGame::gameManager(bool stateKeys[], bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height) // NOTE peut etre passer un pointeur sur kb et mouse !
{
    SE->stop("sounds/menu-dark.wav");
    SE->play("sounds/blackpearl.wav", true);
    if (*switchMode == TOGAME && !camera->camOKGame()) {
        camera->toModeGameSmart();
    }
    else if (*switchMode == TOGAME && camera->camOKGame()) {
        *switchMode = NONE;
    }
    else if (*switchMode == TOMENU && (!camera->camOKMenu())) {
        camera->toModeMenuSmart();
        if (end) {
            player.toCenter();
        }
    }
    else if (*switchMode == TOMENU && (camera->camOKMenu())) {
        *switchMode = NONE;
        *etatGame = MENU; // seulement une fois que la transition est fini, on change l'etat.
    }
    else if (*switchMode == NONE && stateKeys[K_ESC]) {
        *switchMode = TOMENU;
    }
    else {
        Mode::Manager(stateKeys, stateButtons, coordMouse, deltaWheel, time, width, height);
        if (timerFin == 0 && end) {
            if (toEnd && !(stateKeys[K_ENTER] && stateButtons[B_LEFT])) { // et on attend une action pour sortir
                *switchMode = TOMENU;
            }
            if (stateKeys[K_ENTER] || stateButtons[B_LEFT]) {
                toEnd = true;
            }
        }
        else {
            firesManager();
            trajectoriesManager();
            deadEnemiesManager();
            //bonusManager();
            if ((timerFin == INTERVALE_TEMP_FIN) && (end)) {
                killall(); // on vire tout les objet autre que le player
                timerFin--;
            }
            if ((timerFin <= INTERVALE_TEMP_FIN) && (end)) {
                timerFin--;
            }
            if (timerFin == INTERVALE_TEMP_FIN) {
                playerManager(); // si c'est pas la fin, on peut gere le jeu correctement
                enemiesManager();
                bombManager();
                collisionManager(); //vérifie les collisions et detruie le vaisseau/missile/bonus si nécéssaire
            }
            if ((timersGenEnemy.empty()) ||  (player.isMort())) {
                end = true; // c'est la fin, on bloque les fonctions du jeu.
                if (player.isMort())
		    SE->play("sounds/cri2.wav",false);
            }
        }
    }

    //Pour le fun
    cout << (char)0x0D << friendFires.size() +  enemiesFires.size()<<" missile(s) " << flush;

}


void ModeGame::getRender(vector<instance>* instances, vector<instance>* instances2D) {

    // on recupere toute les instances a afficher
    vector<Actor> vActor;
    vector<Actor>::iterator itA;
    list<ActorMissile>::iterator itAM;
    list<ActorPhysique>::iterator itAP;
    // le player
    instances->push_back(player.getInstance());

    // le enemies
    list<Trajectory>::iterator it_traj;
    //NOTE La boucle qui suit semble ne pas fonctionner !!!
    for (it_traj = trajectories.begin(); it_traj != trajectories.end(); it_traj++)
    {
        list<ActorEnemy>::iterator it_enn;
        list<ActorEnemy> enemies = it_traj->getEnemies();
        for (it_enn=enemies.begin(); it_enn != enemies.end(); it_enn++)
        {
            instances->push_back(it_enn->getInstance());
        }
    }
    for (itAM=enemiesFires.begin(); itAM!= enemiesFires.end(); itAM++) {
        instances->push_back(itAM->getInstance());
    }
    for (itAM=friendFires.begin(); itAM!= friendFires.end(); itAM++) {
        instances->push_back(itAM->getInstance());
    }
    for (itAP=deadEnemies.begin(); itAP!= deadEnemies.end(); itAP++) {
        instances->push_back(itAP->getInstance());
    }
    instances->push_back(bomb.getInstance());

    // les text, score et health et End si c'est la fin
    if (*etatGame == GAME && *switchMode == NONE) {
        // on affiche le score ..., et autre info
        score.getRender(instances2D);
        health.getRender(instances2D);
        if (end && player.isMort() && timerFin == 0) {
            vActor = tEndDead.getText();
            for (itA=vActor.begin(); itA!=vActor.end(); itA++) {
                instances2D->push_back(itA->getInstance());
            }
        }
        else if (end && timerFin == 0) {
            vActor = tEndWin.getText();
            for (itA=vActor.begin(); itA!=vActor.end(); itA++) {
                instances2D->push_back(itA->getInstance());
            }
        }
    }
}
/**
*NOTE j'ai fait une version un peu compliqué du déplacement du joueur pour montrer les possibilités de
* ActorPhysique. Cette simulation est physiquement correcte mais ne correpond pas du tout à ce qu'il y'a d'abitude
* dans les jeux. Cependant, je trouve le concept interressant, ça oblige le joueur à mieux anticiper ses
* trajectoires.
*/
void ModeGame::playerManager()
{
    /*
    vect accl={0,0,0};
    if (stateKeys[parametre->getLeft()])  {// -x
        accl.x-=10;
    }
    if (stateKeys[parametre->getRight()]) {// +x
        accl.x+=10;
    }
    if (stateKeys[parametre->getUp()]) { // +y
        accl.z-=20;
    }
    if (stateKeys[parametre->getDown()]) { // -y
        accl.z+=20;
    }
    player.setAcceleration( accl );
    */
    vect velo={0,0,0};
    if (stateKeys[K_LEFT])  {// -x
        velo.x-=8;
    }
    if (stateKeys[K_RIGHT]) {// +x
        velo.x+=8;
    }
    if (stateKeys[K_UP]) { // +y
        velo.z-=8;
    }
    if (stateKeys[K_DOWN]) { // -y
        velo.z+=8;
    }
    player.setVelocity( velo );



    player.update(dTime);
    // TODO ameliorer definition des bords

    vect p={player.getPosition().x,player.getPosition().y,player.getPosition().z}, r={0,0,0}, s={0.1,0.1,0.1};
    vect pLeft={player.getPosition().x-0.3,player.getPosition().y,player.getPosition().z};
    vect pRight={player.getPosition().x+0.3,player.getPosition().y,player.getPosition().z};
    vect vel={player.getVelocity().x/3,player.getVelocity().y/3,player.getVelocity().z/3};

    if ((((stateKeys[K_TIR]) || (stateButtons[B_LEFT])) and timerGenShoot<=0))
    {
	SE->play("sounds/single-canon-modif.wav",false);
        ActorMissile fire;
        vel.z -= random(15,18);
        vel.x += random(-0.5,0.5); // si le vaisseau a une rotation, on l'applique legerment au boulet

        fire=ActorMissile(models->getMharpon(), p, r, s, 200);
        fire.setVelocity( vel );
        friendFires.push_back(fire); // on double la pussance des boulet tire a l'avant

        timerGenShoot=INTERVALE_TEMP_SHOOT;
    }
    if ((((stateKeys[K_TIR_SECOND]) || (stateButtons[B_RIGHT])) and timerGenShootGros<=0))
    {
	SE->play("sounds/multi-canon.wav",false);
        ActorMissile fire;
        for (float f =-0.8;f<=0.8;f+=0.2)
        {
            if (random(0,1) < 0.9) {
                vel.x = 0;
                vel.z = 0;
// 	        pRight.x=player.getPosition().x+0.3;
                pRight.z=player.getPosition().z+f;
                vel.x += random(15,18);
                vel.z += random(-0.5,0.5);
                fire=ActorMissile(models->getMbouletP(), pRight, r, s);
                fire.setVelocity( vel);
                friendFires.push_back(fire);
            }
            if (random(0,1) < 0.9) {
                vel.x = 0;
                vel.z = 0;
// 	        pLeft.x=player.getPosition().x+0.3;
                pLeft.z=player.getPosition().z+f;
                vel.x -= random(15,18);
                vel.z += random(-0.5,0.5);
                fire=ActorMissile(models->getMbouletP(),pLeft, r, s);
                fire.setVelocity( vel);
                friendFires.push_back(fire);
            }
        }
        timerGenShootGros=INTERVALE_TEMP_SHOOT_GROS;
    }
    else {
        timerGenShoot--;
        timerGenShootGros--;
    }
}

void ModeGame::firesManager()
{
    list<ActorMissile>::iterator it;

    for (it=friendFires.begin(); it!=friendFires.end(); it++) {
        it->update(dTime);
    }
    for (it=enemiesFires.begin(); it!=enemiesFires.end(); it++) {
        it->update(dTime);
    }
}


void ModeGame::bombManager() {
    if (bomb.getPosition().z > 20 || bomb.getScale().x < 0.02) {
        vect p={random(-12,12),0,random(-18,-15)}, r={0,0,0}, s={0.6,0.6,0.6}, v={0,0,4};
        bomb = ActorMissile(models->getMBomb(), p, r, s, 500, 0.4);
        bomb.setVelocity(v);
    }
    else {
        bomb.update (dTime); // si la bomb n'est pas morte, on update sa trajectoir.
    }
}


void ModeGame::trajectoriesManager() {
    bool timerGenEnemyStarted = FALSE;
    bool timerOffMet = FALSE; // Booleen pour savoir s'il est toujours utile de faire une decrementation du timer (s'il reste des sequences à demarrer)
    list<Trajectory>::iterator it_traj = trajectories.begin();
    list<int>::iterator it_gene = timersGenEnemy.begin();
    // On parcourt les trajectoires pour supprimer celles qui n'ont plus d'ennemis, et pour démarrer la génération des ennemis de chaque trajectoire
    // de facon ordonnée (ex : on démarre la première trajectoire, puis au prochain top, on en démarre une autre...)
    while (it_traj != trajectories.end())
    {
        // Si tous les ennemis ont ete generes et qu'il n'en reste plus, alors on supprime la trajectoire et son timer
        if (it_traj->getRecordNumbers().size() == 0 && it_traj->getEnemies().size() == 0) {
            it_traj = trajectories.erase(it_traj);
            it_gene = timersGenEnemy.erase(it_gene);
        }
        else {
            if (*it_gene == TIMER_OFF)
            {
                if (timerGenTrajectorySequence <= 0) {
                    *it_gene = it_traj->getInterval(); // On demarre le timer d'ennemis de cette trajectoire en quelque sorte
                    timerGenTrajectorySequence = INTERVALE_TEMP_TRAJECTORY_SEQUENCE;
                    timerGenEnemyStarted = TRUE;
                }
                timerOffMet = TRUE;
            }
            it_traj++;
            it_gene++;
        }
    }
    if (timerOffMet && timerGenTrajectorySequence > 0 && !timerGenEnemyStarted)
        timerGenTrajectorySequence--;
}

void ModeGame::enemiesManager()
{
    list<Trajectory>::iterator it_traj = trajectories.begin();
    list<int>::iterator it_gene = timersGenEnemy.begin();
    for (int i = 0; i<(int)timersGenEnemy.size(); i++)
    {
        // On met a jour la position de chacun des ennemis presents sur la trajectoire
        list<ActorEnemy>::iterator it_enn;
        list<ActorEnemy> enemies = it_traj->getEnemies();
        for (it_enn = enemies.begin(); it_enn != enemies.end(); it_enn++) {
            it_enn->update(dTime);
            if ((it_enn->getTimerFire()<=0) && ((player.getPosition().z-it_enn->getPosition().z)>0))
            {
                vect p={it_enn->getPosition().x,it_enn->getPosition().y,it_enn->getPosition().z}, r={0,0,0}, s={0.2,0.2,0.2};
                vect pDest={(-it_enn->getPosition().x+player.getPosition().x),(-it_enn->getPosition().y+player.getPosition().y),(-it_enn->getPosition().z+player.getPosition().z)};
                float coef = sqrt(pDest.x*pDest.x + pDest.z* pDest.z)/8;
                ActorMissile fire;
                fire=ActorMissile(models->getMbouletE(), p, r, s);
                fire.setCoefVel(coef);
                fire.setVelocity( pDest );
                enemiesFires.push_back(fire);
                it_enn->resetTimerFire();
            }
        }
        it_traj->setEnemies(enemies);
        if (it_traj->getRecordNumbers().size() && *it_gene <=0)
        {
            int rec_num = *(it_traj->getRecordNumbers().begin());
            vect r={0,0,0}, s={1,1,1};
            ActorEnemy e(models->getEnemiesInfos()[rec_num].idModel,it_traj->getInitialPosition(),r,s,&(*it_traj),models->getEnemiesInfos()[rec_num].health,
            models->getEnemiesInfos()[rec_num].damages,models->getEnemiesInfos()[rec_num].score,models->getEnemiesInfos()[rec_num].mask_radius/1000);
            it_traj->addEnemy(e);
            it_traj->removeFirstRecordNumber(); // On enleve le numero d'enregistrement pour dire qu'on a bien cree l'ennemi
            *it_gene = it_traj->getInterval();
        }
        else
            *it_gene = *it_gene - 1;
        it_traj++;
        it_gene++;
    }

}


void ModeGame::deadEnemiesManager()
{
    list<ActorPhysique>::iterator itDE;
    for (itDE=deadEnemies.begin(); itDE!= deadEnemies.end();) {
        itDE->update(dTime);
        if (itDE->getScale().x<0.01)
            itDE=deadEnemies.erase(itDE);
        else
        {
            vect rotation={0,itDE->getRotation().y+4,itDE->getRotation().z+4};
            vect scale={itDE->getScale().x*0.95,itDE->getScale().y*0.95,itDE->getScale().z*0.95};
            itDE->setRotation(rotation);
            itDE->setScale(scale);
            itDE++;
        }
    }
}

void ModeGame::collisionManager()
{
    //pour l'instant ne sert a virer les objets sortant du cadre
    // si on rentre en collision avec la bordure exterieur on efface l'object
    player.colisionBord(width,height); // donner une leger rotation au vaisseau

    /* gestion colision enemis avec player ou tir joueur. */
    list<Trajectory>::iterator it_traj;
    for (it_traj = trajectories.begin(); it_traj != trajectories.end(); it_traj++)
    {
        list<ActorEnemy> enemies = it_traj->getEnemies();
        list<ActorEnemy>::iterator it_enn;
        it_enn = enemies.begin();
        while (it_enn != enemies.end())
        {
            if (it_enn->sortieEcran(width+5,height+5)) {
                it_enn = enemies.erase(it_enn); // On efface l'element et on pointe sur le suivant (donc pas besoin de faire un it_enn++)
            } else {
                it_enn->colisionFires(&friendFires); // idem avec les tir Player
                if (it_enn->colision(&player)) { // on regarde si l'ennemi est en colision avec le playerManager
		    SE->play("sounds/explosion.wav",false);
                    player.setHealth(-it_enn->getDamages());
                    playerHeart = TEMP_BROUILLAGE_CAM_PLAYER_HEARTH;
                    deadEnemies.push_back(ActorPhysique(it_enn->getIdModel(),it_enn->getPosition(),it_enn->getRotation(),  it_enn->getScale()));
                    deadEnemies.back().setVelocity(it_enn->getVelocity());
                    it_enn = enemies.erase(it_enn);
                }
                else if (it_enn->isMort()) { // si l'ennemi est mort, on le suprime et on modifie le score
		    SE->play("sounds/cri.wav",false);
                    score.setScore(it_enn->getScore());
                    deadEnemies.push_back(ActorPhysique(it_enn->getIdModel(),it_enn->getPosition(),it_enn->getRotation(),  it_enn->getScale()));
                    deadEnemies.back().setVelocity(it_enn->getVelocity());
                    it_enn = enemies.erase(it_enn); // On efface l'element et on pointe sur le suivant (donc pas besoin de faire un it_enn++)
                }
                else
                    it_enn++;
            }
        }
        it_traj->setEnemies(enemies);
    }

    /* gestion colision  tir joueur */
    list<ActorMissile>::iterator itAP;
    itAP = friendFires.begin();
    while (itAP!=friendFires.end())
    {
        if (itAP-> sortieEcran(width+5,height+5))
            itAP = friendFires.erase(itAP);
        else
            itAP++;
    }

    /* gestion colision tir enemis */
    itAP=enemiesFires.begin();
    while (itAP!=enemiesFires.end())
    {
        if (itAP-> sortieEcran(width+5,height+5))
            itAP = enemiesFires.erase(itAP);
        else
            itAP++;
    }

    if (player.colisionFires(&enemiesFires)) {
        playerHeart = TEMP_BROUILLAGE_CAM_PLAYER_HEARTH_MISSILE;
    }


    /* gestion colision bomb */
    if (bomb.colisionFires(&friendFires)) { // regarde s'il y a colision avec les tir du joueur
        deadEnemies.push_back(ActorPhysique(bomb.getIdModel(),bomb.getPosition(),bomb.getRotation(),  bomb.getScale()));
        deadEnemies.back().setVelocity(bomb.getVelocity());
        vect s={0,0,0}; // on la cache pour la faire reaparaitre plus tart sous la forme d'une nouvelle bomb
        bomb.setScale(s);
    }
    else if (player.colision(&bomb)) { // on regarde s'il y a colision avec le joueur en lui meme
        vect s={0,0,0}; // on la cache pour la faire reaparaitre plus tart sous la forme d'une nouvelle bomb
        bomb.setScale(s);
        player.setHealth(-bomb.getDamage());
        playerHeart = TEMP_BROUILLAGE_CAM_PLAYER_HEARTH_LONG;
    }
    health.setHealth(player.getHealth()); // al la fin, on met a jour l'objet graphi sante
}

void ModeGame::killall() {
    /* gestion colision enemis avec player ou tir joueur. */
    list<Trajectory>::iterator it_traj;
    for (it_traj = trajectories.begin(); it_traj != trajectories.end(); it_traj++)
    {
        list<ActorEnemy> enemies = it_traj->getEnemies();
        list<ActorEnemy>::iterator it_enn;
        it_enn = enemies.begin();
        while (it_enn != enemies.end())
        {
            deadEnemies.push_back(ActorPhysique(it_enn->getIdModel(),it_enn->getPosition(),it_enn->getRotation(),  it_enn->getScale()));
            deadEnemies.back().setVelocity(it_enn->getVelocity());
            it_enn = enemies.erase(it_enn);
//         it_enn++;
        }
        it_traj->setEnemies(enemies);
    }
    deadEnemies.push_back(ActorPhysique(bomb.getIdModel(),bomb.getPosition(),bomb.getRotation(),  bomb.getScale()));
    deadEnemies.back().setVelocity(bomb.getVelocity());
    vect s={0,0,0}; // on la cache pour la faire reaparaitre plus tart sous la forme d'une nouvelle bomb
    bomb.setScale(s);
    friendFires.clear();
    enemiesFires.clear();
}