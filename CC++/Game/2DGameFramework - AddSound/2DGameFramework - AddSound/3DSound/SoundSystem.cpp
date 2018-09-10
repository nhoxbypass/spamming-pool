#include "SoundSystem.h"
#include "Utils.h"

SoundSystem* SoundSystem::instance = NULL;

SoundSystem::SoundSystem(unsigned int channels) {
	listener		= NULL;
	masterVolume	= 1.0f;

	Log("Creating SoundSystem!");
	Log("Found the following devices:");
	Log(alcGetString(NULL,ALC_DEVICE_SPECIFIER));

	device = alcOpenDevice(NULL);	//Open the 'best' device

	if(!device) {
		Log("Failed to create SoundSystem! (No valid device!)");
	}

	Log("SoundSystem created with device: ");
	Log(alcGetString(device,ALC_DEVICE_SPECIFIER));

	context = alcCreateContext(device,NULL);
	alcMakeContextCurrent(context);

	alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);

	for(unsigned int i = 0; i < channels; ++i) {
		ALuint source;

		alGenSources(1,&source);
		ALenum error = alGetError();

		if(error == AL_NO_ERROR)	{
			sources.push_back(new OALSource(source));
		}
		else{
			break;
		}
	}

}

SoundSystem::~SoundSystem(void)	{
	for(vector<SoundPlayer*>::iterator i = temporaryEmitters.begin(); i != temporaryEmitters.end(); ++i) {
		delete (*i);
	}

	for(vector<OALSource*>::iterator i = sources.begin(); i != sources.end(); ++i) {
		alDeleteSources(1, &(*i)->source);
		delete (*i);
	}
	/*for (int i=0;emitters.size();i++)
	{
		Delete(emitters[i]);
	}*/
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void		SoundSystem::Update(float msec) {
	UpdateListener();
	UpdateTemporaryEmitters(msec);

	//Update values for every node, whether in range or not
	for(vector<SoundPlayer*>::iterator i = emitters.begin(); i != emitters.end(); ++i) {
		(*i)->UpdateSoundState(msec);
	}

	CullNodes();	//First off, remove nodes that are too far away

	if(emitters.size() > sources.size()) {
		std::sort(emitters.begin(), emitters.end(), SoundPlayer::CompareNodesByPriority);	//Then sort by priority

		DetachSources(emitters.begin() + (sources.size()+1), emitters.end());		//Detach sources from nodes that won't be covered this frame
		AttachSources(emitters.begin(), emitters.begin() + (sources.size()));	//And attach sources to nodes that WILL be covered this frame
	}
	else{
		AttachSources(emitters.begin(), emitters.end());//And attach sources to nodes that WILL be covered this frame
	}

	emitters.clear();	//We're done for the frame! empty the emitters list
}

void	SoundSystem::CullNodes() {
	for(vector<SoundPlayer*>::iterator i = emitters.begin(); i != emitters.end();) {

		float length;

		if((*i)->GetIsGlobal()) {
			length = 0.0f;
		}
		else{
			if (listener!=0)
				length = Distance(listener->GetPosition(),(*i)->GetPosition());
			else
				length=0.0f;
		}
		
		if(length > (*i)->GetRadius() || !(*i)->GetSound() || (*i)->GetTimeLeft() < 0) {
			(*i)->DetachSource();	//Important!
			i = emitters.erase(i);
		}
		else{
			++i;
		}
	}
}

void	SoundSystem::DetachSources(vector<SoundPlayer*>::iterator from, vector<SoundPlayer*>::iterator to) {
	for(vector<SoundPlayer*>::iterator i = from; i != to; ++i) {
		(*i)->DetachSource();
	}
}

void	SoundSystem::AttachSources(vector<SoundPlayer*>::iterator from, vector<SoundPlayer*>::iterator to) {
	for(vector<SoundPlayer*>::iterator i = from; i != to; ++i) {
		if(!(*i)->GetSource()) {	//Don't attach a new source if we already have one!
			(*i)->AttachSource(GetSource());
		}
	}
}

OALSource*	SoundSystem::GetSource() {
	for(vector<OALSource*>::iterator i = sources.begin(); i != sources.end(); ++i) {
		OALSource*s = *i;
		if(!s->inUse) {
			return s;
		}
	}
	return NULL;
}

void		SoundSystem::SetMasterVolume(float value)	{
	value = MaxF(0, value);
	value = MinF(1, value);
	masterVolume = value;
	alListenerf(AL_GAIN,masterVolume);
}

void	SoundSystem::UpdateListener() {
	if(listener)	{
		Matrix worldMat = listener->GetWorldMatrix();
		Vector3 worldPos = listener->GetPosition();

		Vector3 dirup[2];
		//forward
		dirup[0].x = -worldMat.m[0][2];
		dirup[0].y = -worldMat.m[1][2];
		dirup[0].z = -worldMat.m[2][2];
		//Up
		dirup[1].x = worldMat.m[0][1];
		dirup[1].y = worldMat.m[1][1];
		dirup[1].z = worldMat.m[2][1];

		alListenerfv(AL_POSITION,(float*)&worldPos);
		alListenerfv(AL_ORIENTATION,(float*)&dirup);
	}
}

void	SoundSystem::PlaySound(Sound* s, Vector3 position) {
	SoundPlayer* n = new SoundPlayer();
	n->SetLooping(false);
	n->SetPosition(position);
	n->SetSound(s);
	temporaryEmitters.push_back(n);
}

void	SoundSystem::PlaySound(Sound* s, SoundPriority p,bool isLooping) {
	SoundPlayer* n = new SoundPlayer();
	n->SetLooping(isLooping);
	n->SetSound(s);
	n->SetIsGlobal(true);
	n->SetPriority(p);
	temporaryEmitters.push_back(n);
}

void SoundSystem::PauseSound(Sound *s)
{
	for(vector<SoundPlayer*>::iterator i = emitters.begin(); i != emitters.end(); ++i) {
		if ((*i)->GetSound()==s)
		{
			alSourcePause((*i)->GetSource()->source);
			
			break;
		}
	}
}

void	SoundSystem::UpdateTemporaryEmitters(float msec) {
	for(vector<SoundPlayer*>::iterator i = temporaryEmitters.begin(); i != temporaryEmitters.end(); ) {
		if((*i)->GetTimeLeft() < 0.0f && !(*i)->GetLooping()) {
			delete (*i);
			i = temporaryEmitters.erase(i);
		}
		else{
			(*i)->Update(msec);
			++i;
		}
	}
}