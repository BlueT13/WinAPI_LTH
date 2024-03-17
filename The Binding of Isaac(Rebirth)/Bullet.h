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
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void IsCrashed();

	void BulletStateUpdate(float _DeltaTime);
	void BulletMove(float _DeltaTime);
	void BulletCrashed(float _DeltaTime);
	void BulletStateChange(EBulletState _State);

private:
	UImageRenderer* BulletRenderer = nullptr;
	UCollision* BulletCollision = nullptr;
	const FVector RendererSize = { 64,64 };

	EBulletState BulletState = EBulletState::None;
	bool IsDestroy = false;

	float BulletDamage = 1.0f;
	float BulletLiveTime = 0.0f;
	float BulletDestroyTime = 0.8f;

	FVector Dir = FVector::Zero;
	float BulletSpeed = 500.0f;
};

