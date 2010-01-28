#ifndef SOUNDENGINE_H_
#define SOUNDENGINE_H_


//-------------------
#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string.h>
#include <pthread.h>
//-------------------
using namespace std;


class SoundEngine
{
	public:
	SoundEngine();
	~SoundEngine();

	void load(string file);
	void unload(string file);
	
	void play(string file,bool loop);
	void stop(string file);
	bool isFinished(string file);
	
	private:
		map<string,unsigned int> files;
		map<unsigned int,pthread_t> threads;
		map<unsigned int,unsigned int> sources;
		map<unsigned int,bool> playing;
};


/*

void GetDevices(vector<string>& Devices);
bool InitOpenAL(const char* DeviceName = NULL);
ALuint LoadSound(const string& Filename);
void ShutdownOpenAL();
void * playASound(void* soundToPlay);
void playSound(string soundToPlay);
*/
#endif