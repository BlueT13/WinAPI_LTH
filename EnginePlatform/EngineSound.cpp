#include "EngineSound.h"

// lib를 사용하는법

// Debug 일때는
// #pragma comment(lib, "ThirdParty\\FMOD\\inc\\fmodL_vc.lib")
#pragma comment(lib, "fmodL_vc.lib")

// Release 일때는 
// #pragma comment(lib, "fmod_vc.lib")

UEngineSound::UEngineSound() 
{
}

UEngineSound::~UEngineSound() 
{
}


void UEngineSound::Load(std::string_view _Path, std::string_view _Name)
{
	// UEngineSound* NewSound = new UEngineSound();
}