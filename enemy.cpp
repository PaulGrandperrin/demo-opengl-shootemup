#include "enemy.h"
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

void EnemyInfosFile::close() {
  file.close();
}

bool EnemyInfosFile::isEnded() {
  bool at_the_end = file.peek() == EOF;
  if (file.eof())
	file.clear();
  return at_the_end;
}

void EnemyInfosFile::begin() {
  file.seekg(ios_base::beg);
}

void EnemyInfosFile::end() {
  file.seekp(ios_base::end);
}

void EnemyInfosFile::write(string s) {
	size_t l = s.size();
	file.write((char*) &l, sizeof(l));
	file.write(s.data(), l);
}

void EnemyInfosFile::write(int i) {
  file.write((char*) &i, sizeof(i));
}

void EnemyInfosFile::read(string & s) {
// 	size_t l;
	int j; // fonctionne avec un entier car sizeof(int) = 4, et sizeof(size_t =8) sur PC seb et sizeof(size_t =4) sur PC romain
	file.read((char*) &j, sizeof(int));
// 	cout << " bonjour : " << l <<  "  si " << sizeof(j)  << endl;
	char readString[j + 1];
// 	cout << " bonjour : 2" << endl;
	file.read(readString, j);
// 	cout << " bonjour : 3" << endl;
	readString[j] = '\0';
	s = readString;
}

void EnemyInfosFile::read(int & i) {
  file.read((char*) &i, sizeof(i));
}

void EnemyInfosFile::enterInfos() {
  string name;
  int health;
  cout << "Please enter a new Enemy :" << endl;
  cout << "Existing file name (without the extension and the parent directory) :" << endl;
  getline(cin,name);
  do {
    cout << "Health :" << endl;
    cin >> health;
    cin.ignore(256,'\n');
  } while(health < 0);
  this->write(name);
  this->write(health);
}

void EnemyInfosFile::displayContent() {
  begin();
  int i = 1;
  while(!isEnded())
  {
    string s;
    int health;
    read(s);
    read(health);
    cout << "#" << i << endl;
    cout << "File name : \"" << s << "\"" << endl;
    cout << "Health : " << health << endl << endl;
    i++;
  }
}
