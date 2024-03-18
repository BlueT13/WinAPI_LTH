#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ATrophy : public AActor
{
public:
	// constrcuter destructer
	ATrophy();
	~ATrophy();

	// delete Function
	ATrophy(const ATrophy& _Other) = delete;
	ATrophy(ATrophy&& _Other) noexcept = delete;
	ATrophy& operator=(const ATrophy& _Other) = delete;
	ATrophy& operator=(ATrophy&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* TrophyRenderer = nullptr;
	UCollision* TrophyCollision = nullptr;
};

