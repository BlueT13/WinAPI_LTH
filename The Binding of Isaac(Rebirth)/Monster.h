#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"
#include "Player.h"

// Ό³Έν :
class AMonster : public AActor
{
public:
	// constrcuter destructer
	AMonster();
	~AMonster();

	// delete Function
	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void MonsterStateUpdate(float _DeltaTime);
	virtual void MonsterIdle(float _DeltaTime);
	virtual void MonsterMove(float _DeltaTime);
	virtual void MonsterAttack(float _DeltaTime);
	virtual void MonsterDie(float _DeltaTime);
	virtual void MonsterStateChange(EMonsterState _State);
	virtual void MonsterIdleStart();
	virtual void MonsterMoveStart();
	virtual void MonsterAttackStart();
	virtual void MonsterDirCheck();

	std::string GetMonsterAnimationName(std::string _Name);


	EMonsterState MonsterState = EMonsterState::None;
	EActorDir MonsterDirState = EActorDir::None;

	UImageRenderer* MonsterRenderer = nullptr;
	UCollision* MonsterCollision = nullptr;

	FVector MoveVector = FVector::Zero;
	FVector MoveAcc = { 0.0f, 0.0f };
	FVector StopAcc = { 0.0f, 0.0f };

	APlayer* Player;
	FVector PlayerLocation;
private:
};

