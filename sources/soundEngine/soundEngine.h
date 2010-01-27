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
#include <string.h>
//-------------------
using namespace std;

void GetDevices(vector<string>& Devices);
bool InitOpenAL(const char* DeviceName = NULL);
ALuint LoadSound(const string& Filename);
void ShutdownOpenAL();
int playASound(string soundToPlay);

#endif