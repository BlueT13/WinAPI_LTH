#pragma once
#include <EngineCore/Actor.h>

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



protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* CreateIntroAnimation(UImageRenderer* _intro, int _introIndex);
	int CurAniCount = 0;
	UImageRenderer* intro;
};

