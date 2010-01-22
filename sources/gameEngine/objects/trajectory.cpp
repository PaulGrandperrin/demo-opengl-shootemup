#include "./trajectory.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

////////////////////////////////////////
// Trajectory
////////////////////////////////////////

Trajectory::Trajectory(vect initialPosition, int interval) {
  this->initialPosition = initialPosition;
  this->interval = interval;
}

void Trajectory::addKeyState(t_key_state s) {
  keyStates.push_back(s);
}

void Trajectory::addRecordNumber(int rec_num) {
  recordNumbers.push_back(rec_num);
}

void Trajectory::addEnemy(ActorEnemy e) {
  enemies.push_back(e);
}

void Trajectory::removeFirstRecordNumber() {
  recordNumbers.pop_front();
}

////////////////////////////////////////
// Trajectory File
////////////////////////////////////////

TrajectoryFile::TrajectoryFile(string fileName) {
	open(fileName);
}

TrajectoryFile::~TrajectoryFile() {
	close();
}

void TrajectoryFile::open(string fileName) {
	this->fileName = fileName;
	file.open(fileName.data(), ios_base::in | ios_base::out
			| ios_base::binary | ios_base::app);
	if (file.fail() == EOF) {
		cout << "Unable to open \"" << fileName
				<< "\"" << endl;
		exit(0);
	}
}

void TrajectoryFile::close() {
	file.close();
}

bool TrajectoryFile::isEnded() {
	bool at_the_end = file.peek() == EOF;
	if (file.eof())
		file.clear();
	return at_the_end;
}

void TrajectoryFile::begin() {
	file.seekg(ios_base::beg);
}

void TrajectoryFile::end() {
	file.seekp(ios_base::end);
}

void TrajectoryFile::write(t_key_state s) {
	file.write((char*) &(s.ax), sizeof(s.ax));
	file.write((char*) &(s.ay), sizeof(s.ay));
	file.write((char*) &(s.az), sizeof(s.az));
	file.write((char*) &(s.vx), sizeof(s.vx));
	file.write((char*) &(s.vy), sizeof(s.vy));
	file.write((char*) &(s.vz), sizeof(s.vz));
	file.write((char*) &(s.t), sizeof(s.t));
}

void TrajectoryFile::read(t_key_state & s) {
	file.read((char*) &(s.ax), sizeof(s.ax));
	file.read((char*) &(s.ay), sizeof(s.ay));
	file.read((char*) &(s.az), sizeof(s.az));
	file.read((char*) &(s.vx), sizeof(s.vx));
	file.read((char*) &(s.vy), sizeof(s.vy));
	file.read((char*) &(s.vz), sizeof(s.vz));
	file.read((char*) &(s.t), sizeof(s.t));
}

void TrajectoryFile::read(Trajectory & t) {
	// Lecture de la position initiale
	vect initPos;
	file.read((char*) &(initPos.x), sizeof(initPos.x));
	file.read((char*) &(initPos.y), sizeof(initPos.y));
	file.read((char*) &(initPos.z), sizeof(initPos.z));
	// Lecture de l'intervalle
	int interval;
	file.read((char*) &interval, sizeof(interval));
	t = Trajectory(initPos, interval);
	// Lecture des positions cles
	int nb;
	file.read((char*) &nb, sizeof(nb));
	t_key_state ks;
	for(int i = 0; i<nb; i++) {
		read(ks);
		t.addKeyState(ks);
	}
	// Lecture des numeros d'enregistrement des ennemis
	file.read((char*) &nb, sizeof(nb));
	int rec_num;
	for(int i = 0; i<nb; i++) {
		file.read((char*) &rec_num, sizeof(rec_num));
		// NOTE : (romain) avant, je créais les ennemis directement lors de la création de la trajectoire, mais j'ai décidé de faire
		// différemment en créant un tableau de numéros d'enregistrements dans le fichier de chacun des ennemis de la trajectoire.
		t.addRecordNumber(rec_num);
		/*
		// On crée un nouvel ennemi avec toutes les infos récupérées
		Enemy e((enemiesInfos->at(rec_num)).idModel,initPos,{0,0,0},{1,1,1},&t,(enemiesInfos->at(rec_num)).health);
		t.addEnemy(e);
		*/
	}
}

void TrajectoryFile::read(list<Trajectory> & l) {
	begin();
	Trajectory t;
	while(!isEnded()) {
		read(t);
		l.push_back(t);
	}
}

void TrajectoryFile::enterInfos() {
	vect initPos;
	int interval;
	cout << "Please enter a new trajectory :" << endl;
	cout << "Initial Position (x,y,z) :" << endl;
	cin >> initPos.x;
	cin.ignore(256,'\n');
	cin >> initPos.y;
	cin.ignore(256,'\n');
	cin >> initPos.z;
	cin.ignore(256,'\n');
	do {
		cout << "Interval (X*20ms) :" << endl;
		cin >> interval;
		cin.ignore(256,'\n');
	} while(interval < 20);
	char choix;
	list<t_key_state> keyStates;
	do {
		t_key_state ks;
		cout << "Key State :" << endl;
		cout << "(ax,ay,az,vx,vy,vz,t) :" << endl;
		cin >> ks.ax;
		cin.ignore(256,'\n');
		cin >> ks.ay;
		cin.ignore(256,'\n');
		cin >> ks.az;
		cin.ignore(256,'\n');
		cin >> ks.vx;
		cin.ignore(256,'\n');
		cin >> ks.vy;
		cin.ignore(256,'\n');
		cin >> ks.vz;
		cin.ignore(256,'\n');
		cin >> ks.t;
		cin.ignore(256,'\n');
		keyStates.push_back(ks);
		do {
			cout << "Do you want to add another key state ? (y or n)" << endl;
			cin >> choix;
			cin.ignore(256,'\n');
		} while(choix != 'y' && choix != 'n');
	} while (choix == 'y');
	list<int> list_num_rec;
	do {
		int num_rec;
		cout << "Enemy :" << endl;
		do {
			cout << "Which one do you want to add to the trajectory ?" << endl;
			// NOTE Faudra faire gaffe de saisir un numero existant
			cin >> num_rec;
			cin.ignore(256,'\n');
		} while(num_rec < 0);
		list_num_rec.push_back(num_rec);
		do {
			cout << "Do you want to add another enemy ? (y or n)" << endl;
			cin >> choix;
			cin.ignore(256,'\n');
		} while(choix != 'y' && choix != 'n');
	} while (choix == 'y');
	// On enregistre les infos dans le fichier
	file.write((char*) &(initPos.x), sizeof(initPos.x));
	file.write((char*) &(initPos.y), sizeof(initPos.y));
	file.write((char*) &(initPos.z), sizeof(initPos.z));
	file.write((char*) &interval, sizeof(interval));
	int size = keyStates.size();
	file.write((char*) &size, sizeof(size));
	list<t_key_state>::iterator itk;
	for (itk = keyStates.begin(); itk!= keyStates.end(); itk++)
	{
		write(*itk);
	}
	size = list_num_rec.size();
	file.write((char*) &size, sizeof(size));
	list<int>::iterator iti;
	for (iti = list_num_rec.begin(); iti!= list_num_rec.end(); iti++)
	{
		file.write((char*) &(*iti), sizeof(*iti));
	}
}

void TrajectoryFile::displayContent() {
	begin();
	Trajectory t;
	int i = 1;
	while(!isEnded()) {
		read(t);
		vect initPos = t.getInitialPosition();
		cout << "Trajectory #" << i << " :" << endl;
		cout << "  Initial Position : (" << initPos.x << "," << initPos.y << "," << initPos.z << ")" << endl;
		cout << "  Interval : " << t.getInterval() << endl;
		cout << "  Key States :" << endl;
		vector<t_key_state>::iterator itk;
		vector<t_key_state> keystates = t.getKeyStates();
		int j = 1;
		for (itk = keystates.begin(); itk != keystates.end(); itk++)
		{
			cout << "    P" << j << " : (ax = " << itk->ax << ", ay = " << itk->ay << ", az = " << itk->az << ", vx = " << itk->vx << ", vy = " << itk->vy << ", vz = " << itk->vz << ", t = " << itk->t << ")" << endl;
			j++;
		}
		cout << "  Enemies :" << endl;
		list<int>::iterator ite;
		list<int> record = (t.getRecordNumbers());
		j = 1;
		for (ite = record.begin(); ite != record.end(); ite++)
		{
			cout << "    Enemy #" << j << " : " << *ite << endl;
			j++;
		}
		i++;
	}
}
