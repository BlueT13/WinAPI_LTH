#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

// Ό³Έν :
class AMonsterBullet : public AActor
{
public:
	// constrcuter destructer
	AMonsterBullet();
	~AMonsterBullet();

	// delete Function
	AMonsterBullet(const AMonsterBullet& _Other) = delete;
	AMonsterBullet(AMonsterBullet&& _Other) noexcept = delete;
	AMonsterBullet& operator=(const AMonsterBullet& _Other) = delete;
	AMonsterBullet& operator=(AMonsterBullet&& _Other) noexcept = delete;
	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void IsCrashed();

	void MonsterBulletStateUpdate(float _DeltaTime);
	void MonsterBulletMove(float _DeltaTime);
	void MonsterBulletCrashed(float _DeltaTime);
	void MonsterBulletStateChange(EBulletState _State);

	APlayer* Player = nullptr;

private:
	UImageRenderer* MonsterBulletRenderer = nullptr;
	UCollision* MonsterBulletCollision = nullptr;
	const FVector RendererSize = { 64,64 };

	EBulletState MonsterBulletState = EBulletState::None;
	bool IsDestroy = false;

	float MonsterBulletLiveTime = 0.0f;
	float MonsterBulletDestroyTime = 0.8f;

	FVector Dir = FVector::Zero;
	float Speed = 300.0f;
	float MonsterBulletDamage = 2.0f;
};

