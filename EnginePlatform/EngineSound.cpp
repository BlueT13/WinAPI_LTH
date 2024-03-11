#include "EngineSound.h"
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineDebug.h>

// lib�� ����ϴ¹�

// Debug �϶���
// #pragma comment(lib, "ThirdParty\\FMOD\\inc\\fmodL_vc.lib")
#pragma comment(lib, "fmodL_vc.lib")

// Release �϶��� 
// #pragma comment(lib, "fmod_vc.lib")

std::map<std::string, UEngineSound*> UEngineSound::Resources;
float UEngineSound::GlobalVolume = 1.0f;

void UEngineSoundPlayer::SetVolume(float _Volume)
{
	Control->setVolume(_Volume * UEngineSound::GlobalVolume);
}


// FMOD�� ���õ� ���带 �ε��Ҽ� �ִ� ����.
FMOD::System* SoundSystem = nullptr;

class ResControl
{
public:
	ResControl() 
	{
		if (FMOD_RESULT::FMOD_OK != FMOD::System_Create(&SoundSystem))
		{
			MsgBoxAssert("���� �ý��� ������ �����߽��ϴ�.");
			return;
		}

		if (FMOD_RESULT::FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgBoxAssert("���� �ý��� ������ �����߽��ϴ�.");
			return;
		}
	}
	~ResControl() 
	{
		UEngineSound::ResourcesRelease();
		SoundSystem->release();
		SoundSystem = nullptr;
	}
};

ResControl Inst;

void UEngineSound::ResourcesRelease()
{
	for (std::pair<const std::string, UEngineSound*>& Pair : Resources)
	{
		delete Pair.second;
	}

	Resources.clear();
}

UEngineSound::UEngineSound() 
{
}

UEngineSound::~UEngineSound() 
{
}


void UEngineSound::ResLoad(std::string_view _Path)
{

	// FMOD_DEFAULT; => �ݺ������ �ȵȴ�.
	SoundSystem->createSound(_Path.data(), FMOD_LOOP_NORMAL, nullptr, &SoundHandle);
	if (nullptr == SoundHandle)
	{
		MsgBoxAssert("���� �ε忡 �����߽��ϴ�." + std::string(_Path));
		return;
	}

	// SoundSystem->playSound(SoundHandle, nullptr, false, nullptr);
}

void UEngineSound::SetGlobalVolume(float _Value)
{
	GlobalVolume = _Value;

	if (GlobalVolume <= 0.0f)
	{
		GlobalVolume = 0.0f;
	}

	if (GlobalVolume >= 1.0f)
	{
		GlobalVolume = 1.0f;
	}
}

UEngineSoundPlayer UEngineSound::SoundPlay(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == Resources.contains(UpperName))
	{
		MsgBoxAssert("�ε����� ���带 ����Ϸ��� �߽��ϴ�." + UpperName);
		return UEngineSoundPlayer();
	}

	UEngineSound* FindSound = Resources[UpperName];

	UEngineSoundPlayer Result;
	SoundSystem->playSound(FindSound->SoundHandle, nullptr, false, &Result.Control);
	Result.Control->setLoopCount(0);
	Result.SetVolume(1.0f);

	if (nullptr == Result.Control)
	{
		MsgBoxAssert("���� ����� ���� ���� ������ �������� ���߽��ϴ�.");
		return Result;
	}


	return Result;
}

void UEngineSound::Update()
{
	// �������Ӹ��� ȣ��Ǿ�� �Ѵ�.
	// �׷��� FMOD ���̺귯���� �ټ��� ���带 �������ش�.
	if (nullptr == SoundSystem)
	{
		MsgBoxAssert("���� �ý��ۿ� ġ������ ������ �ֽ��ϴ�.");
	}

	SoundSystem->update();
}

void UEngineSound::Load(std::string_view _Path, std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (true == Resources.contains(UpperName))
	{
		MsgBoxAssert("�̹� �ε��� ���ҽ��� �� �ε� �Ϸ��� �߽��ϴ�.");
		return;
	}

	UEngineSound* NewSound = new UEngineSound();
	NewSound->ResLoad(_Path);
	Resources[UpperName] = NewSound;
}