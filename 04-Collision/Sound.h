#pragma once
#include <map>
#include "dxsound.h"

enum eSoundID
{
	SOUND_STAGE1,
	SOUND_HIT_EFFECT,
	SOUND_HURT,
	SOUND_JUMP,
	SOUND_EAT_ITEM
};

class Sound
{
private:
	std::map<eSoundID, CSound*> listSound;
	Sound();
	static Sound* instance;
public:

	~Sound();
	static Sound* GetInstance();
	void loadSound(HWND hwnd);
	void Play(eSoundID);
	void Stop(eSoundID);
	void PlayLoop(eSoundID);
	bool IsPLaying(eSoundID);
};

