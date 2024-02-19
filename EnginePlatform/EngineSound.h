#pragma once
#include <string>
#include <string_view>

// #include나 이런걸 사용하더라도 실제로 그 코드가 실행되지 않으면
// 컴파일러가 무시한다.
#include "ThirdParty\FMOD\inc\fmod.hpp"

// 이녀석은 선생님 본래 관리 방식을 보여드리겠습니다.

// 설명 :
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

