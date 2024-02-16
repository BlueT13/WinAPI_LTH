#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AIntroImage :public AActor
{
public:
	// constrcuter destructer
	AIntroImage();
	~AIntroImage();

	// delete Function
	AIntroImage(const AIntroImage& _Other) = delete;
	AIntroImage(AIntroImage&& _Other) noexcept = delete;
	AIntroImage& operator=(const AIntroImage& _Other) = delete;
	AIntroImage& operator=(AIntroImage&& _Other) noexcept = delete;



protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

