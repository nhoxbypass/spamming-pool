#pragma once
#include <algorithm>
#include <vector>
#include "Sound.h"
#include "al.h"
#include "alc.h"
#include "Entity2D.h"
#include "SoundPlayer.h"



class SoundPlayer;

struct OALSource {
	ALuint	source;
	bool	inUse;

	OALSource(ALuint src) {
		source	= src;
		inUse	= false;
	}
};

#include "SoundPlayer.h"

enum SoundPriority;

class SoundSystem	{
public:
	static void Initialise(unsigned int channels = 8) {
		instance = new SoundSystem(channels);
	}

	static void Destroy() {
		delete instance;
	}

	static SoundSystem* GetSoundSystem() {
		return instance;
	}

	void		SetListener(Entity2D* s)	{listener = s;}
	Entity2D*	GetListener()				{return listener;}

	void		AddSoundPlayer(SoundPlayer* s)	{emitters.push_back(s);}

	void		Update(float msec);

	void		SetMasterVolume(float value);

	void		PlaySound(Sound* s, Vector3 position);
	void		PlaySound(Sound* s, SoundPriority p,bool isLooping=false);
	void		PauseSound(Sound* s);
protected:
	SoundSystem(unsigned int channels = 128);
	~SoundSystem(void);

	void		UpdateListener();

	void		DetachSources(vector<SoundPlayer*>::iterator from, vector<SoundPlayer*>::iterator to);
	void		AttachSources(vector<SoundPlayer*>::iterator from, vector<SoundPlayer*>::iterator to);

	void		CullNodes();

	OALSource*	GetSource();

	void		UpdateTemporaryEmitters(float msec);

	vector<OALSource*>	sources;
	
	vector<SoundPlayer*>	emitters;
	vector<SoundPlayer*>	temporaryEmitters;

	Entity2D*			listener;

	ALCcontext*			context;
	ALCdevice*			device;

	float				masterVolume;

	static SoundSystem* instance;
};