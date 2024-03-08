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
		MoveVector = _Dir;
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
	const FVector RendererSize = { 64,64 };

	EBulletState BulletState = EBulletState::None;
	bool IsDestroy = false;

	float BulletLiveTime = 0.0f;
	float BulletDestroyTime = 0.8f;

	FVector MoveVector = FVector::Zero;
	float Speed = 500.0f;
	FVector LastMoveVector = FVector::Zero;

	void AddMoveVector(const FVector& _DirDelta);
	void BulletMoveUpdate(float _DeltaTime);
	void CalMoveVector(float _DeltaTime);
	void CalLastMoveVector(float _DeltaTime);
	void MoveLastMoveVector(float _DeltaTime);
};

