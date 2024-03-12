#pragma once
#include "Monster.h"
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

// Ό³Έν :
class APooter : public AMonster
{
public:
	// constrcuter destructer
	APooter();
	~APooter();

	// delete Function
	APooter(const APooter& _Other) = delete;
	APooter(APooter&& _Other) noexcept = delete;
	APooter& operator=(const APooter& _Other) = delete;
	APooter& operator=(APooter&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MonsterStateUpdate(float _DeltaTime) override;
	void Spawn(float _DeltaTime);
	void Move(float _DeltaTime);
	void Attack(float _DeltaTime);
	void CreateMonsterBullet(FVector _Dir);
	void Die(float _DeltaTime);
	void MonsterStateChange(EMonsterState _State) override;
	void SpawnStart();
	void MoveStart();
	void AttackStart();
	void DieStart();

	UCollision* PlayerCheckCollision = nullptr;
	FTransform PlayerCheckCollisionTrans;

private:
	float MonsterBulletCoolTime = 0.0f;
	float MonsterFireRate = 1.0f;
};

