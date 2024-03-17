#pragma once
#include "Monster.h"
#include "ContentsHelper.h"
#include <EngineCore/Actor.h>
#include <EnginePlatform/EngineSound.h>

// Ό³Έν :
class ARedBoomfly : public AMonster
{
public:
	// constrcuter destructer
	ARedBoomfly();
	~ARedBoomfly();

	// delete Function
	ARedBoomfly(const ARedBoomfly& _Other) = delete;
	ARedBoomfly(ARedBoomfly&& _Other) noexcept = delete;
	ARedBoomfly& operator=(const ARedBoomfly& _Other) = delete;
	ARedBoomfly& operator=(ARedBoomfly&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MonsterStateUpdate(float _DeltaTime) override;
	void Spawn(float _DeltaTime);
	void Move(float _DeltaTime);
	void Die(float _DeltaTime);
	void CreateMonsterBullet(FVector _Dir);
	void MonsterStateChange(EMonsterState _State) override;
	void SpawnStart();
	void MoveStart();
	void DieStart();

	void MonsterTouchWall(EActorDir _Dir) override;

private:
	UEngineSoundPlayer DeathSound;
};

