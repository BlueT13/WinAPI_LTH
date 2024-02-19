#pragma once
#include <string>
#include <string_view>

// #include�� �̷��� ����ϴ��� ������ �� �ڵ尡 ������� ������
// �����Ϸ��� �����Ѵ�.
#include "ThirdParty\FMOD\inc\fmod.hpp"

// �̳༮�� ������ ���� ���� ����� �����帮�ڽ��ϴ�.

// ���� :
class UEngineSound
{
public:
	// constrcuter destructer
	UEngineSound();
	~UEngineSound();

	// delete Function
	UEngineSound(const UEngineSound& _Other) = delete;
	UEngineSound(UEngineSound&& _Other) noexcept = delete;
	UEngineSound& operator=(const UEngineSound& _Other) = delete;
	UEngineSound& operator=(UEngineSound&& _Other) noexcept = delete;

	static void Load(std::string_view _Path, std::string_view _Name);

protected:

private:
	FMOD::Sound* SoundHandle = nullptr;

};

