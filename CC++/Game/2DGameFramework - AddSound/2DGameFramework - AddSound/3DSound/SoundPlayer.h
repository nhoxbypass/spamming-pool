#pragma once
#include "../Utilities/utilities.h"
#include "Sound.h"
#include "SoundSystem.h"

#define NUM_STREAM_BUFFERS 3

enum SoundPriority{
	SOUNDPRIORTY_LOW,
	SOUNDPRIORITY_MEDIUM,
	SOUNDPRIORITY_HIGH,
	SOUNDPRIORITY_ALWAYS
};

struct OALSource;

class SoundPlayer
{
public:
	SoundPlayer(void);
	SoundPlayer(Sound* s);
	~SoundPlayer(void);
	void			Reset();

	void			SetSound(Sound *s);
	Sound*			GetSound()					 {return sound;}

	void			SetPosition(Vector3 pos);
	Vector3			GetPosition();

	void			SetPriority(SoundPriority p) {priority = p;}
	SoundPriority	GetPriority()				 {return priority;}

	void			SetVolume(float volume)		 {volume = min(1.0f, max(0.0f, volume));}
	float			GetVolume()					 {return volume;}

	void			SetLooping(bool state)		 {isLooping = state;}
	bool			GetLooping()				 {return isLooping;}

	void			SetRadius(float value)		 {radius = max(0.0f, value);}
	float			GetRadius()					 {return radius;}

	float			GetPitch()					 {return pitch;}
	void			SetPitch(float value)		 {pitch = value;}

	bool			GetIsGlobal()				 {return isGlobal;}
	void			SetIsGlobal(bool value)		 {isGlobal = value;}

	double			GetTimeLeft()				 {return timeLeft;}

	OALSource*		GetSource()					 {return oalSource;}

	void			UpdateSoundState(float msec);

	static bool		CompareNodesByPriority(SoundPlayer *a, SoundPlayer* b);

	void			AttachSource(OALSource* s);
	void			DetachSource();
	
	virtual void	Update(float msec);

protected:
	Sound*			sound;
	OALSource*		oalSource;
	SoundPriority	priority;
	float			volume;
	float			radius;
	float			pitch;
	bool			isLooping;
	bool			isGlobal;
	double			timeLeft;
	Vector3			mPosition;
	double			streamPos;							
	ALuint			streamBuffers[NUM_STREAM_BUFFERS];	
};