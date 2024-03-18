#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>
#include <EnginePlatform/EngineSound.h>

// Ό³Έν :
class AIntroBackground :public AActor
{
public:
	// constrcuter destructer
	AIntroBackground();
	~AIntroBackground();

	// delete Function
	AIntroBackground(const AIntroBackground& _Other) = delete;
	AIntroBackground(AIntroBackground&& _Other) noexcept = delete;
	AIntroBackground& operator=(const AIntroBackground& _Other) = delete;
	AIntroBackground& operator=(AIntroBackground&& _Other) noexcept = delete;

	static bool IntroEnd;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	float Time = 0.0f;
	float AnimationDurationTime = 0.068f;
	UImageRenderer* intro = nullptr;
	std::list<UEngineFile> AllFileList;
	std::list<UEngineFile> SoundFileList;
	std::list<UEngineFile>::iterator CurIter;

	UEngineSoundPlayer IntroSound;
	UEngineSoundPlayer TitleSound;
};
