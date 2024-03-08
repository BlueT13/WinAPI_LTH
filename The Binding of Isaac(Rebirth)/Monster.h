#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"
#include "Player.h"

// Ό³Έν :
class AMonster : public AActor
{
	friend class ABullet;
	friend class ARoom;
public:
	// constrcuter destructer
	AMonster();
	~AMonster();

	// delete Function
	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

	void SetMonsterRoom(ARoom* _Room);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	virtual void MonsterStateUpdate(float _DeltaTime) {};
	virtual void MonsterStateChange(EMonsterState _State) {};

	APlayer* Player = nullptr;
	FVector PlayerLocation;
	UCollision* PlayerCollision;
	float PlayerMoveMaxSpeed;

	UImageRenderer* MonsterRenderer = nullptr;
	UImageRenderer* SpawnRenderer = nullptr;
	UCollision* MonsterCollision = nullptr;
	EMonsterState MonsterState = EMonsterState::None;

	FVector MonsterPos = FVector::Zero;
	FVector MonsterToPlayerDir = FVector::Zero;
	FVector MonsterToPlayerDirNormal = FVector::Zero;

	ARoom* CurRoom = nullptr;

	float MonsterMoveSpeed = 0.0f;

private:
};

