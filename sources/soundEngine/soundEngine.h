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
	
	unsigned int play(string file,bool loop);
	void stop(unsigned int idPlaying);
	bool isFinished(unsigned int idPlaying);
	
	private:
		vector<pthread_t> threads;
		map<string,unsigned int> ids;
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