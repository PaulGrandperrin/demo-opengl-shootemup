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



bool InitOpenAL(const char* DeviceName = NULL)
{
    // Ouverture du device
    ALCdevice* Device = alcOpenDevice(DeviceName);
    if (!Device)
    {
        cerr << "Impossible d'ouvrir le device par d�faut" << endl;
        return false;
    }

    // Cr�ation du contexte
    ALCcontext* Context = alcCreateContext(Device, NULL);
    if (!Context)
    {
        cerr << "Impossible de cr�er un contexte audio" << endl;
        return false;
    }

    // Activation du contexte
    if (!alcMakeContextCurrent(Context))
    {
        cerr << "Impossible d'activer le contexte audio" << endl;
        return false;
    }

    return true;
}


ALuint LoadSound(const string& Filename)
{
    // Ouverture du fichier audio avec libsndfile
    SF_INFO FileInfos;
    SNDFILE* File = sf_open(Filename.c_str(), SFM_READ, &FileInfos);
    if (!File)
    {
        cerr << "Impossible d'ouvrir le fichier audio" << endl;
        return 0;
    }

    // Lecture du nombre d'�chantillons et du taux d'�chantillonnage (nombre d'�chantillons � lire par seconde)
    ALsizei NbSamples  = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
    ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);

    // Lecture des �chantillons audio au format entier 16 bits sign� (le plus commun)
    vector<ALshort> Samples(NbSamples);
    if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
    {
        cerr << "Impossible de lire les �chantillons stock�s dans le fichier audio" << endl;
        return 0;
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
            return 0;
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
        return 0;
    }

    return Buffer;
}



void ShutdownOpenAL()
{
    // R�cup�ration du contexte et du device
    ALCcontext* Context = alcGetCurrentContext();
    ALCdevice*  Device  = alcGetContextsDevice(Context);

    // D�sactivation du contexte
    alcMakeContextCurrent(NULL);

    // Destruction du contexte
    alcDestroyContext(Context);

    // Fermeture du device
    alcCloseDevice(Device);
}




int playASound(string soundToPlay)
{
    // R�cup�ration des devices disponibles
    //vector<string> Devices;
    //GetDevices(Devices);

    // On affiche la liste � l'utilisateur
    //cout << "Veuillez choisir un device :" << endl << endl;
    //for (size_t i = 0; i < Devices.size(); ++i)
    //    cout << "[" << i << "] " << Devices[i] << endl;

    // Et on le laisse choisir
    //int Choice;
    //cin >> Choice;

    // Initialisation d'OpenAL
    InitOpenAL("ALSA Software");//InitOpenAL(Devices[Choice].c_str());

    // Chargement du fichier audio
    ALuint Buffer = LoadSound(soundToPlay);//"ocean.wav");
    if (Buffer == 0)
        return -1;

    // Cr�ation d'une source
    ALuint Source;
    alGenSources(1, &Source);
    alSourcei(Source, AL_BUFFER, Buffer);

    // On joue le son
    alSourcePlay(Source);

    // On attend qu'il soit termin�
    ALint Status;
    do
    {
        // R�cup�ration et affichage de la position courante de lecture en secondes
        ALfloat Seconds = 0.f;
        alGetSourcef(Source, AL_SEC_OFFSET, &Seconds);
        cout << "\rLecture en cours... " << fixed << setprecision(2) << Seconds << " sec";

        // R�cup�ration de l'�tat du son
        alGetSourcei(Source, AL_SOURCE_STATE, &Status);
    }
    while (Status == AL_PLAYING);

    // Destruction du tampon
    alDeleteBuffers(1, &Buffer);

    // Destruction de la source
    alSourcei(Source, AL_BUFFER, 0);
    alDeleteSources(1, &Source);

    // Fermeture d'OpenAL
    ShutdownOpenAL();

    cout << endl << endl;
    cout << "Son terminé !" << endl;//cout << "Appuyez sur entree pour terminer..." << endl;
    //cin.ignore(10000, '\n');
    //cin.ignore(10000, '\n');

    return 0;
}

#endif