#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"
#include "Player.h"

// Ό³Έν :
class AMonster : public AActor
{
	friend class ABullet;
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
	virtual void MonsterStateUpdate(float _DeltaTime) {};
	virtual void MonsterStateChange(EMonsterState _State) {};

	APlayer* Player = nullptr;
	FVector PlayerLocation;

	UImageRenderer* MonsterRenderer = nullptr;
	UCollision* MonsterCollision = nullptr;
	EMonsterState MonsterState = EMonsterState::None;

	FVector MonsterPos = FVector::Zero;
	FVector MonsterDir = FVector::Zero;
	FVector MonsterDirNormal = FVector::Zero;

private:
};

