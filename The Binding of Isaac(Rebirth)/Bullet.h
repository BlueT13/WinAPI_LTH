#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

// Ό³Έν :
class ABullet : public AActor
{
public:
	// constrcuter destructer
	ABullet();
	~ABullet();

	// delete Function
	ABullet(const ABullet& _Other) = delete;
	ABullet(ABullet&& _Other) noexcept = delete;
	ABullet& operator=(const ABullet& _Other) = delete;
	ABullet& operator=(ABullet&& _Other) noexcept = delete;

	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;
	}

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
	void IsCrashed();

	void BulletStateUpdate(float _DeltaTime);
	void BulletMove(float _DeltaTime);
	void BulletCrashed(float _DeltaTime);
	void BulletStateChange(EBulletState _State);


private:
	UImageRenderer* BulletRenderer = nullptr;
	UCollision* BulletCollision = nullptr;

	FVector Dir = FVector::Zero;
	float Speed = 500.0f;
	const FVector RendererSize = { 64,64 };
	float BulletLiveTime = 0.0f;
	float BulletDestroyTime = 0.8f;

	EBulletState BulletState = EBulletState::None;
	bool IsDestroy = false;
};

