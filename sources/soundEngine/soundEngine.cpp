#include "soundEngine.h"
#include <stdio.h>
#include <stdlib.h>

/** NOTE
 *	Ce code est extremement moche mais il a été fait
 * à l'arache dans le seul but de rajouter un peu
 * de son.....
 * Ne pas regarder plus bas, merci...
*/

void * playInThread(void *idFile);

map<unsigned int,bool>* playingG;

SoundEngine::SoundEngine()
{
	// Ouverture du device
	#ifdef win32
		char DeviceName[]="windows";
	#else
		char DeviceName[]="ALSA Software";
	#endif

	ALCdevice* Device = alcOpenDevice(DeviceName);
	if (!Device)
	{
		cerr << "Impossible d'ouvrir le device par défaut" << endl;
		return;
	}

	// Création du contexte
	ALCcontext* Context = alcCreateContext(Device, NULL);
	if (!Context)
	{
		cerr << "Impossible de créer un contexte audio" << endl;
		return;
	}

	// Activation du contexte
	if (!alcMakeContextCurrent(Context))
	{
		cerr << "Impossible d'activer le contexte audio" << endl;
		return;
	}

	playingG=&playing;
}

SoundEngine::~SoundEngine()
{
	// R�cup�ration du contexte et du device
// 	ALCcontext* Context = alcGetCurrentContext();
// 	ALCdevice*  Device  = alcGetContextsDevice(Context);
// 
// 	// D�sactivation du contexte
// 	alcMakeContextCurrent(NULL);
// 
// 	// Destruction du contexte
// 	alcDestroyContext(Context);
// 
// 	// Fermeture du device
// 	alcCloseDevice(Device);
// 
// 
// 	//TODO tt bien fermer
}

void SoundEngine::load(string file)
{
		// Ouverture du fichier audio avec libsndfile
	SF_INFO FileInfos;
	SNDFILE* File = sf_open(file.c_str(), SFM_READ, &FileInfos);
	if (!File)
	{
		cerr << "Impossible d'ouvrir le fichier audio" << endl;
		return;
	}

	// Lecture du nombre d'�chantillons et du taux d'�chantillonnage (nombre d'�chantillons � lire par seconde)
	ALsizei NbSamples  = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
	ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);

	// Lecture des �chantillons audio au format entier 16 bits sign� (le plus commun)
	vector<ALshort> Samples(NbSamples);
	if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
	{
		cerr << "Impossible de lire les �chantillons stock�s dans le fichier audio" << endl;
		return;
	}

	// Fermeture du fichier
	sf_close(File);

	// D�termination du format en fonction du nombre de canaux
	ALenum Format;
	switch (FileInfos.channels)
	{
		case 1 : Format = AL_FORMAT_MONO16;   break;
		case 2 : Format = AL_FORMAT_STEREO16; break;
		default :
			cerr << "Format audio non support� (plus de 2 canaux)" << endl;
			return;
	}

	// Cr�ation du tampon OpenAL
	ALuint Buffer;
	alGenBuffers(1, &Buffer);

	// Remplissage avec les �chantillons lus
	alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);

	// V�rification des erreurs
	if (alGetError() != AL_NO_ERROR)
	{
		cerr << "Impossible de remplir le tampon OpenAL avec les �chantillons du fichier audio" << endl;
		return;
	}
	
	files.insert(pair<string,unsigned int>(file,Buffer));
	
	playing.insert(pair<unsigned int, bool>(files[file],false));
}

void SoundEngine::unload(string)
{

	
}

void SoundEngine::play(string file,bool loop)
{
	if(playing[files[file]]==false)
	{
		playing[files[file]]=true;
		unsigned int* id=(unsigned int*)malloc(sizeof(unsigned int)*3);
		id[0]=files[file];
		id[1]=loop?true:false;
		

		ALuint Source;
		alGenSources(1, &Source);
		sources.insert(pair<unsigned int,unsigned int>(files[file],Source));
		id[2]=Source;

		
		pthread_t th;
		pthread_create(&th,NULL,
					&playInThread ,
					(void*)id);
		pthread_detach(th);

		threads[files[file]]=th;
	}
}

void SoundEngine::stop(string file)
{
	if(playing[files[file]]==true)
	{
		pthread_cancel(threads[files[file]]);
		alSourcei(sources[files[file]], AL_BUFFER, 0);
		alDeleteSources(1, &sources[files[file]]);
		playing[files[file]]=false;
	}
}

bool SoundEngine::isFinished(string )
{
	return false;//TODO a faire
}


void * playInThread(void *idFile)
{
	// Chargement du fichier audio
	ALuint Buffer = ((ALuint*)idFile)[0];
	unsigned int loop=((ALuint*)idFile)[1];
	ALuint Source=((ALuint*)idFile)[2];
	free((unsigned int*)idFile);

	// Cr�ation d'une source 
	alSourcei(Source, AL_BUFFER, Buffer);
	do
	{
		// On joue le son
		alSourcePlay(Source);

		// On attend qu'il soit terminé
		ALint Status;
		do
		{
			// R�cup�ration de l'�tat du son
			alGetSourcei(Source, AL_SOURCE_STATE, &Status);
			usleep(1); //HACK c'est moche
		}
		while (Status == AL_PLAYING );
	}while(loop);

	// Destruction de la source
	alSourcei(Source, AL_BUFFER, 0);
	alDeleteSources(1, &Source);

	(*(playingG))[Buffer]=false;

	return NULL;
}








/**
void GetDevices(vector<string>& Devices)
{
	// Vidage de la liste
	Devices.clear();

	// R�cup�ration des devices disponibles
	const ALCchar* DeviceList = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

	if (DeviceList)
	{
		// Extraction des devices contenus dans la cha�ne renvoy�e
		while (strlen(DeviceList) > 0)
		{
			Devices.push_back(DeviceList);
			DeviceList += strlen(DeviceList) + 1;
		}
	}
	else
	{
		cerr << "Impossible de r�cup�rer la liste des devices" << endl;
	}
}

*/