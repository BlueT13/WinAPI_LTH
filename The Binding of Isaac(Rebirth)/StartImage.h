#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AStartImage : public AActor
{
public:
	// constrcuter destructer
	AStartImage();
	~AStartImage();

	// delete Function
	AStartImage(const AStartImage& _Other) = delete;
	AStartImage(AStartImage&& _Other) noexcept = delete;
	AStartImage& operator=(const AStartImage& _Other) = delete;
	AStartImage& operator=(AStartImage&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

