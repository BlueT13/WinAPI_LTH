#include "EngineSound.h"

// lib�� ����ϴ¹�

// Debug �϶���
// #pragma comment(lib, "ThirdParty\\FMOD\\inc\\fmodL_vc.lib")
#pragma comment(lib, "fmodL_vc.lib")

// Release �϶��� 
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