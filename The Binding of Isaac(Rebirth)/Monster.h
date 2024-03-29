#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"
#include "Player.h"

// ���� :
class AMonster : public AActor
{
	friend class ARoom;
	friend class ABullet;
	friend class ABomb;
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
	ARoom* GetCurRoom()
	{
		return CurRoom;
	}

	// R = P + 2n(-P��n)
	FVector Reflect(FVector _Dir, FVector _Nor);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	virtual void MonsterStateUpdate(float _DeltaTime) {};
	virtual void MonsterStateChange(EMonsterState _State) {};
	void GetHit(float _Damage);

	APlayer* Player = nullptr;
	FVector PlayerLocation = FVector::Zero;
	UCollision* PlayerCollision = nullptr;
	float PlayerMoveMaxSpeed = 0.0f;

	UImageRenderer* MonsterRenderer = nullptr;
	UImageRenderer* SpawnRenderer = nullptr;
	UCollision* MonsterCollision = nullptr;
	EMonsterState MonsterState = EMonsterState::None;

	FVector MonsterPos = FVector::Zero;
	FVector MonsterToPlayerDir = FVector::Zero;
	FVector MonsterToPlayerDirNormal = FVector::Zero;

	FTransform PlayerCollisionTrans;
	FTransform MonsterCollisionTrans;
	FTransform PlayerCheckCollisionTrans;

	ARoom* CurRoom = nullptr;

	float MonsterHp = 0.0f;
	float MonsterMoveSpeed = 0.0f;

	FVector HitPower = FVector::Zero;
	FVector MonsterMoveVector = FVector::Zero;
	FVector MonsterLastMoveVector = FVector::Zero;

	void MonsterMoveUpdate(float _DeltaTime);
	void CalHitPower(float _DeltaTime);
	void CalLastMoveVector(float _DeltaTime);
	void MoveLastMoveVector(float _DeltaTime);

	virtual void MonsterTouchWall(EActorDir _Dir) {};

private:

	
};

