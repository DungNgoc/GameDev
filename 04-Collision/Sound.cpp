#include "Sound.h"

Sound::Sound() {}
Sound::~Sound() {}

Sound* Sound::instance;

Sound* Sound::GetInstance()
{
	if (instance == nullptr)
		instance = new Sound();
	return instance;
}

void Sound::loadSound(HWND hwnd)
{
	InitDirectSound(hwnd);

	CSound* sound = NULL;
	sound = LoadSound("sounds//stage1.wav");
	listSound[eSoundID::SOUND_STAGE1] = sound;

	sound = LoadSound("sounds//hiteffect.wav");
	listSound[eSoundID::SOUND_HIT_EFFECT] = sound;

	sound = LoadSound("sounds//item.wav");
	listSound[eSoundID::SOUND_EAT_ITEM] = sound;

	sound = LoadSound("sounds//jump.wav");
	listSound[eSoundID::SOUND_JUMP] = sound;

	sound = LoadSound("sounds//hurt.wav");
	listSound[eSoundID::SOUND_HURT] = sound;
	

	
}

void Sound::Play(eSoundID id)
{
	auto sound = listSound[id];
	if (sound != NULL)
		PlaySound(sound);
}

void Sound::PlayLoop(eSoundID id)
{
	auto sound = listSound[id];
	if (sound != NULL)
		LoopSound(sound);
}

void Sound::Stop(eSoundID id)
{
	auto sound = listSound[id];
	if (sound != NULL)
		StopSound(sound);
}

bool Sound::IsPLaying(eSoundID id)
{
	auto sound = listSound[id];
	if (sound != NULL)
		return sound->IsSoundPlaying();
	return false;
}