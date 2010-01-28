#include "./enemy.h"
#include <iostream>
#include <stdlib.h>

////////////////////////////////////////
// Enemy Infos File
////////////////////////////////////////

EnemyInfosFile::EnemyInfosFile(string fileName) {
    open(fileName);
}

EnemyInfosFile::~EnemyInfosFile() {
    close();
}

void EnemyInfosFile::open(string fileName) {
    this->fileName = fileName;
    file.open(fileName.data(), ios_base::in | ios_base::out | ios_base::binary | ios_base::app);
    if (file.fail() == EOF) {
        cout << "Unable to open \"" << fileName << "\"" << endl;
        exit(0);
    }
}

bool EnemyInfosFile::isEnded() {
    bool at_the_end = file.peek() == EOF;
    if (file.eof())
        file.clear();
    return at_the_end;
}

void EnemyInfosFile::enterInfos() {
  // structure du fichier : Nom Sante dommage score mask
  
  string name;
  int health = 0, dommage =0, score=0, mask=0;
  cout << "Please enter a new Enemy :" << endl;
  cout << "Existing file name (without the extension and the parent directory) :" << endl;
  getline(cin,name);
  do {
    cout << "Health :" << endl;
    cin >> health;
    cin.ignore(256,'\n');
  } while(health < 0);
  do {
    cout << "Dommage caused :" << endl;
    cin >> dommage;
    cin.ignore(256,'\n');
  } while(dommage < 0);
  do {
    cout << "Score given :" << endl;
    cin >> score;
    cin.ignore(256,'\n');
  } while(score < 0);
  do {
    cout << "Mask :" << endl;
    cin >> mask;
    cin.ignore(256,'\n');
  } while(mask < 0);
  this->write(name);
  this->writeSpace();
  this->write(health);
  this->writeSpace();
  this->write(dommage);
  this->writeSpace();
  this->write(score);
  this->writeSpace();
  this->write(mask);
  this->writeLine();
}

void EnemyInfosFile::displayContent() { //FIXME probleme passe une fois de trop dans la boucle !!
  begin();
  int i = 1;
  while(!isEnded())
  {
    string s;
    int health = 0, dommage =0, score=0, mask=0;
    read(s);
    read(health);
    read(dommage);
    read(score);
    read(mask);
    if (s!="") {
    cout << "#" << i << endl;
    cout << "File name : \"" << s << "\"" << endl;
    cout << "Health : " << health << endl;
    cout << "Domaage : " << dommage  << endl;
    cout << "Score : " << score << endl;
    cout << "Mask : " << mask<< endl;
//     read(s);
    }
    i++;
  }
}