#pragma once
#include "Monster.h"
#include "Fly.h"
#include "ContentsHelper.h"
#include <EngineCore/Actor.h>
#include <EnginePlatform/EngineSound.h>

// Ό³Έν :
class ADukeOfFlies : public AMonster
{
	friend class AFly;

public:
	// constrcuter destructer
	ADukeOfFlies();
	~ADukeOfFlies();

	// delete Function
	ADukeOfFlies(const ADukeOfFlies& _Other) = delete;
	ADukeOfFlies(ADukeOfFlies&& _Other) noexcept = delete;
	ADukeOfFlies& operator=(const ADukeOfFlies& _Other) = delete;
	ADukeOfFlies& operator=(ADukeOfFlies&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MonsterStateUpdate(float _DeltaTime) override;
	void Spawn(float _DeltaTime);
	void Move(float _DeltaTime);
	void Attack(float _DeltaTime);
	void SpawnFly(float _DeltaTime);
	void SendFly(float _DeltaTime);
	void Die(float _DeltaTime);
	void MonsterStateChange(EMonsterState _State) override;
	void SpawnStart();
	void MoveStart();
	void AttackStart();
	void DieStart();

	void MonsterTouchWall(EActorDir _Dir) override;

private:
	float AttackCoolTime = 0.0f;
	float AttackRate = 1.0f;
	std::vector<AFly*> Flys;
	int SpawnCount = 0;

	UEngineSoundPlayer SpawnSound;
	UEngineSoundPlayer SpawnFlySound;
	UEngineSoundPlayer SendFlySound;
	UEngineSoundPlayer DeathSound;
};

