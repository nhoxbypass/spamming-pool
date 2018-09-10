#pragma once

#include <string>
#include <map>
#include <iostream>
#include <fstream>

#include "al.h"

typedef unsigned long DWORD;
using namespace std;

struct FMTCHUNK {
	short format;
	short channels;
	DWORD srate;
	DWORD bps;
	short balign;
	short samp;
};


class Sound {
public:
	char*			GetData()		{return data;}
	int				GetBitRate()	{return bitRate;}
	float			GetFrequency()	{return freqRate;}
	int				GetChannels()	{return channels;}
	int				GetSize()		{return size;}
	ALuint			GetBuffer()		{return buffer;}
	bool			IsStreaming()	{return streaming;}		
	virtual double	StreamData(ALuint	buffer, double timeLeft){ return 0.0f;}							
	ALenum			GetOALFormat();
	double			GetLength();
	static void		AddSound(string n);
	static Sound*	GetSound(string name);
	static void		DeleteSounds();
protected:
	Sound();
	virtual ~Sound(void);
	/*void			LoadFromWAV(char* filename);
	void			LoadWAVChunkInfo(FILE* file, string &name, unsigned int &size);*/
	void			LoadFromWAV(string filename);
	void			LoadWAVChunkInfo(ifstream &file, string &name, unsigned int &size);
	char*			data;
	ALuint			buffer;
	bool			streaming;			
	float			freqRate;
	double			length;
	unsigned int	bitRate;
	unsigned int	size;
	unsigned int	channels;
	static map<string, Sound*> sounds;
};