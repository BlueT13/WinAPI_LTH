#pragma once
#include "Monster.h"
#include "ContentsHelper.h"
#include <EngineCore/Actor.h>
#include <EnginePlatform/EngineSound.h>

// Ό³Έν :
class ABoomfly : public AMonster
{
public:
	// constrcuter destructer
	ABoomfly();
	~ABoomfly();

	// delete Function
	ABoomfly(const ABoomfly& _Other) = delete;
	ABoomfly(ABoomfly&& _Other) noexcept = delete;
	ABoomfly& operator=(const ABoomfly& _Other) = delete;
	ABoomfly& operator=(ABoomfly&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MonsterStateUpdate(float _DeltaTime) override;
	void Spawn(float _DeltaTime);
	void Move(float _DeltaTime);
	void Die(float _DeltaTime);
	void MonsterStateChange(EMonsterState _State) override;
	void SpawnStart();
	void MoveStart();
	void DieStart();

	void MonsterTouchWall(EActorDir _Dir) override;

private:
	UCollision* ExplosionCollision = nullptr;
	float BombPower = 800.0f;

	UEngineSoundPlayer DeathSound;
};

