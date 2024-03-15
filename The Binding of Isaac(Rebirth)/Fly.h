#pragma once
#include "Monster.h"
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

// Ό³Έν :
class AFly : public AMonster
{
	friend class ADukeOfFlies;
public:
	// constrcuter destructer
	AFly();
	~AFly();

	// delete Function
	AFly(const AFly& _Other) = delete;
	AFly(AFly&& _Other) noexcept = delete;
	AFly& operator=(const AFly& _Other) = delete;
	AFly& operator=(AFly&& _Other) noexcept = delete;

	void SetBoss(AActor* _Boss);

	void SetFlySpawnDir(FVector _Dir)
	{
		FlySpawnDir = _Dir;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MonsterStateUpdate(float _DeltaTime) override;
	void Spawn(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Die(float _DeltaTime);
	void MonsterStateChange(EMonsterState _State) override;
	void SpawnStart();
	void MoveStart();
	void DieStart();

	void MonsterTouchWall(EActorDir _Dir) override;
private:
	AActor* Boss = nullptr;
	float Angle = 0.0f;
	FVector FlySpawnDir = FVector::Zero;
	FVector FlySpinDir = FVector::Zero;
};

