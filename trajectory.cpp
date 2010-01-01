#include "trajectory.h"
#include <iostream>
using namespace std;

////////////////////////////////////////
// Trajectory
////////////////////////////////////////

Trajectory::Trajectory(vect initialPosition, int interval) {
  this->initialPosition = initialPosition;
  this->interval = interval;
}

vect Trajectory::getInitialPosition() {
	return initialPosition;
}

int Trajectory::getInterval() {
  return interval;
}

vector<t_key_state> Trajectory::getKeyStates() {
  return keyStates;
}

list<int> Trajectory::getRecordNumbers() {
  return recordNumbers;
}

list<Enemy> Trajectory::getEnemies() {
  return enemies;
}

void Trajectory::addKeyState(t_key_state s) {
  keyStates.push_back(s);
}

void Trajectory::addRecordNumber(int rec_num) {
  recordNumbers.push_back(rec_num);
}

void Trajectory::addEnemy(Enemy e) {
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
	file.write((char*) &(s.type), sizeof(s.type));
	file.write((char*) &(s.x), sizeof(s.x));
	file.write((char*) &(s.y), sizeof(s.y));
	file.write((char*) &(s.z), sizeof(s.z));
	file.write((char*) &(s.t), sizeof(s.t));
}

/*
NOTE : Je pense pas qu'on s'en servira donc...
void TrajectoryFile::write(Trajectory t) {
	// Ecriture de la position initiale
	vect initPos = t.getInitialPosition();
	file.write((char*) &(initPos.x), sizeof(initPos.x));
	file.write((char*) &(initPos.y), sizeof(initPos.y));
	file.write((char*) &(initPos.z), sizeof(initPos.z));
	// Ecriture de l'intervalle
	float f = t.getInterval();
	file.write((char*) &f, sizeof(f));
	// Ecriture du nombre de positions cles...
	int nb = t.getKeyStates().size();
	file.write((char*) &nb, sizeof(nb));
	// ...suivies des positions cles
	vector<t_key_state>::iterator itk;
	for (itk = t.getKeyStates().begin(); itk!= t.getKeyStates().end(); itk++)
    {
		write(*itk);
    }
	// Ecriture du nombre d'ennemis...
	nb = t.getEnemies().size();
	file.write((char*) &nb, sizeof(nb));
	// ...suivies des numeros d'enregistrement des ennemis dans le fichier des ennemis
	list<Enemy>::iterator ite;
	for (ite = t.getEnemies().begin(); ite!= t.getEnemies().end(); ite++)
    {
		nb = ite->getIdModel();
		vector<EnemyInfo>::iterator itei;
		int i = 0;
		// On cherche l'enregistrement correspondant à l'idModel de l'ennemi courant
		for(itei = enemiesInfos->begin(); itei != enemiesInfos->end() && itei->idModel != nb; itei++)
			i++;
		if(itei != enemiesInfos->end())
			file.write((char*) &i, sizeof(i));
    }
}*/

void TrajectoryFile::read(t_key_state & s) {
	file.read((char*) &(s.type), sizeof(s.type));
	file.read((char*) &(s.x), sizeof(s.x));
	file.read((char*) &(s.y), sizeof(s.y));
	file.read((char*) &(s.z), sizeof(s.z));
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
		cout << "Interval (s) :" << endl;
		cin >> interval;
		cin.ignore(256,'\n');
	} while(interval < 20);
	char choix;
	list<t_key_state> keyStates;
	do {
		t_key_state ks;
		cout << "Key State :" << endl;
		do {
			cout << "Type of the modification ? (0 : acceleration, 1 : velocity)" << endl;
			cin >> ks.type;
			cin.ignore(256,'\n');
		} while(ks.type != 0 && ks.type != 1);
		cout << "(x,y,z,t) :" << endl;
		cin >> ks.x;
		cin.ignore(256,'\n');
		cin >> ks.y;
		cin.ignore(256,'\n');
		cin >> ks.z;
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
		int rank;
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
		file.write((char*) iti, sizeof(*iti));
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
		int j = 1;
		for (itk = t.getKeyStates().begin(); itk!= t.getKeyStates().end(); itk++)
		{
			cout << "    P" << j << " : (" << itk.type << "," << itk.x << "," << itk.y << "," << itk.z << "," << itk.t << ")" << endl;
			j++;
		}
		cout << "  Enemies :" << endl;
		ist<Enemy>::iterator ite;
		j = 1;
		for (ite = t.getEnemies().begin(); ite!= t.getEnemies().end(); ite++)
		{
			cout << "    Enemy #" << j << " : (" << ite->getIdModel() << "," << ite->getHealth() << ")" << endl;
			j++;
		}
		i++;
	}
}