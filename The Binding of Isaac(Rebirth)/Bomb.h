#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

// Ό³Έν :
class ABomb : public AActor
{
public:
	// constrcuter destructer
	ABomb();
	~ABomb();

	// delete Function
	ABomb(const ABomb& _Other) = delete;
	ABomb(ABomb&& _Other) noexcept = delete;
	ABomb& operator=(const ABomb& _Other) = delete;
	ABomb& operator=(ABomb&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void BombStateUpdate(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Explosion(float _DeltaTime);
	void BombStateChange(EBombState _State);

private:
	UImageRenderer* BombRenderer = nullptr;
	UCollision* BombCollision = nullptr;

	EBombState BombState = EBombState::None;

	float BoomTime = 2.0f;
};

